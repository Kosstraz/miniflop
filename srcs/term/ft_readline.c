/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:39:06 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/01 14:17:22 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_empty(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (1);
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	return (1);
}

static void	initialise_line_data(t_data *data)
{
	data->term.caps.lines = tgetnum("li");
	data->term.caps.cols = tgetnum("co");
	data->term.line.buf = (char *)ft_malloc(sizeof(char) * CHUNK, data);
	ft_memset(data->term.line.buf, 0, CHUNK);
	data->term.line.i = 0;
	data->term.line.size = 0;
	data->term.line.next = 0;
}

static void	terminal_handle_keys(t_data *data, char *ch)
{
	if (!ft_strcmp(ch, "\033"))
		free_shell(data);
	if (ft_isprint(ch[0]) || (ch[0] == '\t' && is_empty(data->term.line.buf)))
		print_char(data, ch[0]);
	else if (ch[0] == BCK)
		key_backspace(data);
	else if (!ft_strcmp(ch, DEL))
		key_delete(data);
	else if (ch[0] == '\t')
		key_tab(data);
	else if (!ft_strcmp(ch, KEY_UP))
		key_up(data);
	else if (!ft_strcmp(ch, KEY_DOWN))
		key_down(data);
	else if (!ft_strcmp(ch, KEY_RIGHT))
		key_right(data);
	else if (!ft_strcmp(ch, KEY_LEFT))
		key_left(data);
}

static char	*duplicate_buffer(t_data *data)
{
	char	*rtn;

	rtn = ft_strdup(data->term.line.buf);
	if (!rtn)
		free_shell(data);
	free(data->term.line.buf);
	data->term.line.buf = NULL;
	return (rtn);
}

char	*ft_readline(char *prompt, t_data *data)
{
	int		n;
	int		b_read;
	char	buf[READ];
	char	*rtn;

	n = 1;
	write(1, prompt, ft_strlen(prompt));
	initialise_line_data(data);
	get_cursor_position(data);
	ft_memset(&buf, 0, READ);
	while (buf[0] != 13)
	{
		if (data->term.line.size == CHUNK * n)
			data->term.line.buf = (char *)ft_realloc(data->term.line.buf,
				sizeof(char) * (CHUNK * ++n + 1), data);
		b_read = read(data->term.fd, buf, READ);
		if (b_read == -1)
			free_shell(data);
		buf[b_read] = '\0';
		terminal_handle_keys(data, buf);
	}
	while (data->term.curs.l++ <= data->term.line.last.l)
		write(data->term.fd, "\n", 1);
	rtn = duplicate_buffer(data);
	return (rtn);
}
