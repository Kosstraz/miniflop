/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:30:32 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/07 21:55:38 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// [TAB] to do
// regler le "/"
// selectionner le ez

#include "minishell.h"

static void	print_files_colors(unsigned char type, char *name, int is_select)
{
	if (!is_select)
	{
		if (type == DIRECTORY)
			write(STDOUT_FILENO, BOLD_BLUE, 7);
		else if (type == REG_FILE && is_an_execbin(ft_strdup(name)))
			write(STDOUT_FILENO, BOLD_GREEN, 7);
		else if (type == REG_FILE)
			write(STDOUT_FILENO, BOLD_YELLOW, 7);
		else if (type == F_UNKNOWN)
			write(STDOUT_FILENO, BOLD_RED, 7);
	}
	else
	{
		write(STDOUT_FILENO, UNDERLINE, 4);
		write(STDOUT_FILENO, OVERLINE, 5);
		if (type == DIRECTORY)
			write(STDOUT_FILENO, BOLD_BLUE, 7);
		else if (type == REG_FILE && is_an_execbin(ft_strdup(name)))
			write(STDOUT_FILENO, BOLD_GREEN, 7);
		else if (type == REG_FILE)
			write(STDOUT_FILENO, BOLD_YELLOW, 7);
		else if (type == F_UNKNOWN)
			write(STDOUT_FILENO, BOLD_RED, 7);
	}
}

static void	print_files_loop(t_data *data)
{
	int	len;
	int	nls;
	int	printed;

	printed = -1;
	nls = data->term.line.last.l - data->term.curs.l;
	while (nls--)
		write(1, "\n", 1);
	while (++printed < data->term.tab.cnt)
	{
		if (printed % data->term.tab.max_cnt == 0)
		{
			write(1, "\n", 1);
			data->term.tab.written++;
		}
		print_files_colors(data->term.tab.types[printed],
			data->term.tab.files[printed], (printed == data->term.tab.pos));
		len = ft_strlen(data->term.tab.files[printed]);
		write(1, data->term.tab.files[printed], len);
		write(STDOUT_FILENO, RESET, 4);
		while (len++ < data->term.tab.max_len)
			write(1, " ", 1);
	}
}

void	print_files(t_data *data)
{
	data->term.tab.written = 0;
	write(data->term.fd, data->term.caps.save.cap, data->term.caps.save.len);
	print_files_loop(data);
	write(data->term.fd, data->term.caps.restore.cap,
		data->term.caps.restore.len);
	while (data->term.line.last.l + data->term.tab.written > data->term.caps.lines)
	{
		data->term.curs.l--;
		data->term.line.last.l--;
		move_up(data, 0);
	}
}

void	key_tab(t_data *data)
{
	if (!data->term.tab.is_on)
		enter_tab_mode(data);
	data->term.tab.pos++;
	data->term.tab.pos -= (data->term.tab.pos == data->term.tab.cnt)
		* data->term.tab.cnt;
	print_files(data);
}
