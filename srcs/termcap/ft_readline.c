/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:39:06 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/07 00:14:45 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void terminal_handle_keys(t_data *data, char *ch)
{
	if (data->term.tab.is_on &&
		(ft_isprint(ch[0]) || ch[0] == '\177' || !ft_strcmp(ch, KEY_DEL)))
		tab_reset(data);
	if (ft_isprint(ch[0]))
		print_char(data, ch[0]);
	else if (ch[0] == '\004')
		exit_shell(EXIT_TEXT, data, EXIT_SUCCESS);
	else if (ch[0] == '\177')
		key_backspace(data);
	else if (!ft_strcmp(ch, KEY_DEL))
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

char	*end_read(t_data *data)
{
	if (data->term.tab.is_on)
		tab_reset(data);
	while (data->term.curs.l++ <= data->term.line.last.l)
		write(data->term.fd, "\n", 1);
	free(data->term.line.buf);
	data->term.line.buf = NULL;
	return (NULL);
}

char	*ft_readline(char *prompt, t_data *data)
{
	int		n;
	int		b_read;
	char	buf[READ];

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
		b_read = ft_read(data->term.fd, buf, READ, data);
		buf[b_read] = '\0';
		if (!ft_strcmp(buf, "\003"))
			return (end_read(data));
		terminal_handle_keys(data, buf);
	}
	if (data->term.tab.is_on)
		tab_reset(data);
	while (data->term.curs.l++ <= data->term.line.last.l)
		write(data->term.fd, "\n", 1);
	//end_read(data);
	return (data->term.line.buf);
}
