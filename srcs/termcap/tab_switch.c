/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:08:20 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/08 04:07:46 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tab_reset(t_data *data)
{
	char	*cmd;
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
	write(data->term.fd, data->term.caps.save.cap, data->term.caps.save.len);
	cmd = tgoto(data->term.caps.move.cap, 0, data->term.line.last.l);
	if (!cmd)
		exit_shell("\e[31mtgoto\e[0m", data, EXIT_FAILURE);
	write(data->term.fd, cmd, ft_strlen(cmd));
	write(data->term.fd, data->term.caps.clear.cap, data->term.caps.clear.len);
	write(data->term.fd, data->term.caps.restore.cap,
		data->term.caps.restore.len);
}

// static void	fetch_sub_dir(t_data *data, int *i)
// {
// 	int		len;

// 	*i += (*i > 0 || *i == ' ');
// 	len = ft_strlen(&data->term.line.buf[*i]);
// 	if (!len--)
// 		return ;
// 	while (len > 0 && data->term.line.buf[*i + len] != '/')
// 		len--;
// 	if (!len && data->term.line.buf[*i + len] != '/')
// 		return ;
// 	else if (!len)
// 	{
// 		(*i)++;
// 		return ;
// 	}
// 	ft_printf("\n\n%s\n", &data->term.line.buf[*i]);
// 	data->term.tab.dir = ft_strndup(&data->term.line.buf[*i], len);
// 	if (!data->term.tab.dir)
// 		exit_shell("\e[31mft_strndup\e[0m", data, EXIT_FAILURE);
// 	// data->term.tab.dir_split = ft_split(data->term.tab.dir, '/');
// 	// if (!data->term.tab.dir)
// 	// 	exit_shell("\e[31mft_split\e[0m", data, EXIT_FAILURE);
// 	(*i) += len + 1;
// }

// static void	fetch_tab_ref(t_data *data)
// {
// 	int		i;
// 	int		sze;

// 	data->term.tab.ref = NULL;
// 	i = data->term.line.i - 1 + (data->term.line.i == 0);
// 	while (i && data->term.line.buf[i] != ' ' && data->term.line.buf[i] != 9)
// 		i--;
// 	ft_printf("\n%d", i);
// 	fetch_sub_dir(data, &i);
// 	sze = i;
// 	while (data->term.line.buf[sze] && data->term.line.buf[sze] != ' '
// 		&& data->term.line.buf[sze] != '\t')
// 		sze++;
// 	if (sze != i)
// 	{
// 		data->term.tab.ref =
// 			ft_strndup(&data->term.line.buf[i], sze - i);
// 		if (!data->term.tab.ref)
// 			exit_shell("\e[31mft_strndup\e[0m", data, EXIT_FAILURE);
// 	}
// }

// static char	is_an_execbin_no_free(char *path_to_f)
// {
// 	struct stat	fstat;

// 	stat(path_to_f, &fstat);
// 	if (S_ISREG(fstat.st_mode)
// 		&& (fstat.st_mode & S_IXUSR || fstat.st_mode & S_IXGRP
// 			|| fstat.st_mode & S_IXOTH))
// 		return (1);
// 	return (0);
// }

static void	fetch_tab_ref(t_data *data)
{
	int	i;

	i = data->term.line.i - 1 + (data->term.line.i == 0);
	while (i && data->term.line.buf[i] != ' ' && data->term.line.buf[i] != 9)
		i--;
	i += (i > 0 || data->term.line.buf[i] == ' ');
	data->term.tab.dir = take_dir_no_space(&data->term.line.buf[i]);
	data->term.tab.ref = take_absocmd_no_space(&data->term.line.buf[i], data);
}

static void	fetch_dir_contents_loop_exec(t_data *data, DIR *dir)
{
	char			*tmp;
	struct dirent	*dirent;

	errno = 0;
	dirent = readdir(dir);
	while (dirent)
	{
		tmp = ft_strdup(dirent->d_name);
		if (dirent->d_type == DIRECTORY
			|| (dirent->d_type == REG_FILE && is_an_execbin(tmp)))
		{
			data->term.tab.types[data->term.tab.cnt] = dirent->d_type;
			ft_memmove(data->term.tab.files[data->term.tab.cnt++],
				dirent->d_name, ft_strlen(dirent->d_name));
		}
	}
	if (errno)
		exit_shell("\e[31mreaddir\e[0m", data, EXIT_FAILURE);
}

static void	fetch_dir_contents_loop(t_data *data, DIR *dir)
{
	struct dirent	*dirent;

	errno = 0;
	dirent = readdir(dir);
	while (dirent)
	{
		if ((!data->term.tab.ref && dirent->d_name[0] != '.')
			|| !ft_strncmp(data->term.tab.ref,
				dirent->d_name, ft_strlen(data->term.tab.ref)))
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
	if (data->term.tab.dir)
		ft_printf("\n%s\n", data->term.tab.dir);
	else
		ft_printf("\nNULL\n");
	if (data->term.tab.ref)
		ft_printf("\n%s\n", data->term.tab.ref);
	else
		ft_printf("\nNULL\n");
	fetch_dir_contents(data);
	if (!data->term.tab.files[0][0])
	{
		tab_reset(data);
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
