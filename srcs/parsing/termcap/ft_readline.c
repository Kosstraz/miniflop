/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:39:06 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/03 02:41:56 by cachetra         ###   ########.fr       */
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

static void terminal_handle_keys(t_data *data, char *ch)
{
	if (ft_isprint(ch[0]) || (ch[0] == '\t' && is_empty(data->term.line.buf)))
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

static char	*duplicate_buffer(t_data *data)
{
	char	*rtn;

	if (!data->term.line.buf)
		return (NULL);
	rtn = ft_strdup(data->term.line.buf);
	if (!rtn)
		exit_shell("\e[1;31mft_strdup\e[0m", data, EXIT_FAILURE);
	free(data->term.line.buf);
	data->term.line.buf = NULL;
	return (rtn);
}

char	*handle_interrupt(t_data *data)
{
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
			return (handle_interrupt(data));
		terminal_handle_keys(data, buf);
	}
	while (data->term.curs.l++ <= data->term.line.last.l)
		write(data->term.fd, "\n", 1);
	return (duplicate_buffer(data));
}
