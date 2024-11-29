/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:39:06 by cachetra          #+#    #+#             */
/*   Updated: 2024/11/29 15:42:46 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialise_line_data(t_data *data)
{
	data->term.caps.lines = tgetnum("li");
	data->term.caps.cols = tgetnum("co");
	data->term.line.total = B_CHUNK;
	data->term.line.buf =
		(char *)ft_malloc(sizeof(char) * (B_CHUNK + 1), data);
	ft_memset(data->term.line.buf, 0, B_CHUNK + 1);
	data->term.line.i = 0;
	data->term.line.size = 0;
	data->term.line.next = 0;
}

static void	terminal_handle_keys(t_data *data, char *ch, char *prompt)
{
	if (data->term.tab.is_on &&
		(ft_isprint(ch[0]) || ch[0] == '\177' || !ft_strcmp(ch, KEY_DEL)))
		tab_reset(data, 1);
	if (ft_isprint(ch[0]))
		print_char(data, ch[0]);
	else if (ch[0] == '\r' && data->term.tab.is_on)
		tab_select(data, 0);
	else if (ch[0] == '\004' && (!data->term.line.buf || !data->term.line.buf[0]) && !data->heredoc_is_active)
		exit_shell(EXIT_TEXT, data, EXIT_SUCCESS);
	else if (ch[0] == CTRL_L)
		make_ctrl_l(data, prompt);
	else if (ch[0] == '\177')
		key_backspace(data);
	else if (!ft_strcmp(ch, KEY_DEL))
		key_delete(data);
	else if ((ch[0] == '\t' && (!data->term.line.buf || !data->term.line.buf[0]))) // real tab (ctrl + tab + v) fuck it
		write_spacetab(data);
	else if (ch[0] == '\t')
		key_tab(data);
	else if (!ft_strcmp(ch, KEY_T_UP))
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
		tab_reset(data, 1);
	while (data->term.curs.l++ <= data->term.line.last.l)
		write(data->term.fd, "\n", 1);
	free(data->term.line.buf);
	data->term.line.buf = NULL;
	return (NULL);
}

void	resize_line_buffer(t_data *data)
{
	data->term.line.total += B_CHUNK;
	data->term.line.buf = (char *)ft_realloc(data->term.line.buf,
					sizeof(char) * (data->term.line.total + 1), data);
}

char	*ft_readline(char *prompt, t_data *data)
{
	int		b_read;
	char	buf[READ];

	write(1, prompt, ft_strlen(prompt));
	initialise_line_data(data);
	get_cursor_position(data);
	ft_memset(buf, 0, READ);
	while (1)
	{
		if (data->term.line.size == data->term.line.total)
			resize_line_buffer(data);
		b_read = ft_read(data->term.fd, buf, READ, data);
		buf[b_read] = '\0';
		if (!ft_strcmp(buf, "\003"))
		{
			data->ret_cmd = 130;
			setenvval("?", ft_itoa(data->ret_cmd), &data->env);
			if (!data->heredoc_is_active)
				return (end_read(data));
			else
			{
				end_read(data);
				return (ft_strdup("\003"));
			}
		}
		if ((buf[0] == '\r' && !data->term.tab.is_on))
			break ;
		terminal_handle_keys(data, buf, prompt);
	}
	tab_reset(data, 1);
	while (data->term.curs.l++ <= data->term.line.last.l)
		write(data->term.fd, "\n", 1);
	data->ret_cmd = 0;
	return (data->term.line.buf);
}
