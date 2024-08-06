/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:08:20 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/06 23:41:31 by cachetra         ###   ########.fr       */
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
	data->term.tab.prev_line = 0;
	data->term.tab.pos = -1;
	data->term.tab.ref = NULL;
	ft_memset(&data->term.tab.types, 0, sizeof(int) * CHUNK);
	ft_memset(&data->term.tab.files, 0, sizeof(char) * CHUNK * CHUNK);
	write(data->term.fd, data->term.caps.save.cap, data->term.caps.save.len);
	cmd = tgoto(data->term.caps.move.cap,
		data->term.line.last.c, data->term.line.last.l);
	if (!cmd)
		exit_shell("\e[1;31mtgoto\e[0m", data, EXIT_FAILURE);
	write(data->term.fd, cmd, ft_strlen(cmd));
	write(data->term.fd, data->term.caps.clear.cap, data->term.caps.clear.len);
	write(data->term.fd, data->term.caps.restore.cap,
		data->term.caps.restore.len);
}

static void	fetch_tab_ref(t_data *data)
{
	int		i;
	int		sze;

	data->term.tab.ref = NULL;
	i = data->term.line.i - 1 + (data->term.line.i == 0);
	while (i && data->term.line.buf[i] != ' ' && data->term.line.buf[i] != 9)
		i--;
	sze = i - (i != 0);
	while (data->term.line.buf[sze] && data->term.line.buf[sze] != ' '
		&& data->term.line.buf[sze] != '\t')
		sze++;
	if (sze != i - (i != 0))
	{
		data->term.tab.ref =
			ft_strndup(&data->term.line.buf[i + (i != 0)], sze);
		if (!data->term.tab.ref)
			exit_shell("\e[31mft_strndup\e[0m", data, EXIT_FAILURE);
	}
}

static void	fetch_dir_contents(char *filename, t_data *data)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(filename);
	if (!dir)
		exit_shell("\e[31mopendir\e[0m", data, EXIT_FAILURE);
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
	closedir(dir);
}

void	enter_tab_mode(t_data *data)
{
	int	i;
	int	curr;

	i = -1;
	data->term.tab.prev_line = data->term.curs.l;
	data->term.tab.is_on = 1;
	fetch_tab_ref(data);
	// a modifier ici : '.'
	fetch_dir_contents(".", data);
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
