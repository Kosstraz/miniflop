/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:08:20 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/08 22:39:39 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tab_clear(t_data *data)
{
	char	*cmd;

	write(data->term.fd, data->term.caps.save.cap, data->term.caps.save.len);
	cmd = tgoto(data->term.caps.move.cap, 0, data->term.line.last.l);
	if (!cmd)
		exit_shell("\e[31mtgoto\e[0m", data, EXIT_FAILURE);
	write(data->term.fd, cmd, ft_strlen(cmd));
	write(data->term.fd, data->term.caps.clear.cap, data->term.caps.clear.len);
	write(data->term.fd, data->term.caps.restore.cap,
		data->term.caps.restore.len);
}

void	tab_reset(t_data *data, int clear)
{
	data->term.tab.is_on = 0;
	data->term.tab.max_cnt = 0;
	data->term.tab.max_len = 0;
	data->term.tab.cnt = 0;
	data->term.tab.written = 0;
	data->term.tab.pos = -1;
	free(data->term.tab.dir);
	data->term.tab.dir = NULL;
	free(data->term.tab.ref);
	data->term.tab.ref = NULL;
	ft_memset(data->term.tab.types, 0, sizeof(int) * S_CHUNK);
	ft_memset(data->term.tab.files, 0, sizeof(char) * S_CHUNK * S_CHUNK);
	if (clear && data->term.line.last.l != data->term.caps.lines)
		tab_clear(data);
}

static void	fetch_tab_ref(t_data *data)
{
	int	i;

	i = data->term.line.i - 1 + (data->term.line.i == 0);
	while (i && data->term.line.buf[i] != ' ' && data->term.line.buf[i] != 9)
		i--;
	i += (i > 0 || data->term.line.buf[i] == ' ');
	data->term.tab.dir = fetch_dir_name(&data->term.line.buf[i]);
	data->term.tab.ref = fetch_file_name(&data->term.line.buf[i]);
}

static void	fetch_dir_contents_loop_exec(t_data *data, DIR *dir)
{
	int				len;
	char			*tmp;
	struct dirent	*dirent;

	errno = 0;
	dirent = readdir(dir);
	len = ft_strlen(data->term.tab.ref);
	while (dirent)
	{
		tmp = ft_strdup(dirent->d_name);
		if ((dirent->d_type == DIRECTORY
			|| (dirent->d_type == REG_FILE && is_an_execbin(tmp)))
			&& (!ft_strncmp(data->term.tab.ref, dirent->d_name, len)
				|| (!data->term.tab.ref && dirent->d_name[0] != '.')))
		{
			data->term.tab.types[data->term.tab.cnt] = dirent->d_type;
			ft_memmove(data->term.tab.files[data->term.tab.cnt++],
				dirent->d_name, ft_strlen(dirent->d_name));
		}
		errno = 0;
		dirent = readdir(dir);
	}
	if (errno)
		exit_shell("\e[31mreaddir\e[0m", data, EXIT_FAILURE);
}

static void	fetch_dir_contents_loop(t_data *data, DIR *dir)
{
	int				len;
	struct dirent	*dirent;

	errno = 0;
	dirent = readdir(dir);
	len = ft_strlen(data->term.tab.ref);
	while (dirent)
	{
		if ((!data->term.tab.ref && dirent->d_name[0] != '.')
			|| !ft_strncmp(data->term.tab.ref,
				dirent->d_name, len))
		{
			data->term.tab.types[data->term.tab.cnt] = dirent->d_type;
			ft_memmove(data->term.tab.files[data->term.tab.cnt++],
				dirent->d_name, ft_strlen(dirent->d_name));
		}
		errno = 0;
		dirent = readdir(dir);
	}
	if (errno)
		exit_shell("\e[31mreaddir\e[0m", data, EXIT_FAILURE);
}

static void	fetch_dir_contents(t_data *data)
{
	DIR				*dir;

	errno = 0;
	if (!data->term.tab.dir)
		dir = opendir(".");
	else
		dir = opendir(data->term.tab.dir);
	if (!dir)
		return ;
	if  (!ft_strcmp(data->term.tab.dir, "./"))
		fetch_dir_contents_loop_exec(data, dir);
	else
		fetch_dir_contents_loop(data, dir);
	closedir(dir);
}

void	enter_tab_mode(t_data *data)
{
	int	i;
	int	curr;

	i = -1;
	data->term.tab.is_on = 1;
	fetch_tab_ref(data);
	/*int fd = open(ft_strjoin(ft_itoa(ez++), ".txt"), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_putendl_fd(data->term.tab.dir, fd);
	ft_putendl_fd(data->term.tab.ref, fd);
	close(fd);*/
	fetch_dir_contents(data);
	if (!data->term.tab.files[0][0])
	{
		tab_reset(data, 0);
		return ;
	}
	while (++i < data->term.tab.cnt)
	{
		curr = ft_strlen(data->term.tab.files[i]);
		if (curr <= data->term.tab.max_len)
			continue;
		data->term.tab.max_len = curr;
	}
	data->term.tab.max_len += 2;
	data->term.tab.max_cnt = data->term.caps.cols / data->term.tab.max_len;
}
