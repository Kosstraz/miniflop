/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:01:40 by cachetra          #+#    #+#             */
/*   Updated: 2024/11/07 19:23:39 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arrow_keys_tab(t_data *data, int t)
{
	if (t == LEFT)
	{
		data->term.tab.pos--;
		data->term.tab.pos += (data->term.tab.pos == -1) * data->term.tab.cnt;
	}
	else if (t == RIGHT)
	{
		data->term.tab.pos++;
		data->term.tab.pos -= (data->term.tab.pos == data->term.tab.cnt)
			* data->term.tab.cnt;
	}
	else if (t == T_UP)
	{
		if (data->term.tab.pos >= data->term.tab.max_cnt)
			data->term.tab.pos -= data->term.tab.max_cnt;
	}
	else if (t == DOWN)
	{
		if (data->term.tab.pos < data->term.tab.cnt - data->term.tab.max_cnt)
			data->term.tab.pos += data->term.tab.max_cnt;
	}
	print_files(data);
	return (t);
}

static void	key_delete_test(t_data *data)
{
	char	*tmp;

	if (!data->term.line.next)
		return ;
	tmp = (char *)ft_malloc(sizeof(char) * data->term.line.next, data);
	ft_memmove(tmp, &data->term.line.buf[data->term.line.i + 1], data->term.line.next);
	write(data->term.fd, data->term.caps.save.cap, data->term.caps.save.len);
	write(data->term.fd, data->term.caps.clear.cap, data->term.caps.clear.len);
	write_stored_dont_move(&data->term, data->term.line.i, tmp, data->term.line.next);
	write(data->term.fd, data->term.caps.restore.cap, data->term.caps.restore.len);
	free(tmp);
	data->term.line.next--;
	data->term.line.size--;
	update_last(&data->term, 0);
}

int	key_up(t_data *data)
{
	char	*history;

	if (data->term.tab.is_on)
		return (arrow_keys_tab(data, T_UP));
	else
	{
		if (!data->history.original_line)
			data->history.original_line = data->term.line.buf;
		//else
		//{
		//	for (size_t i = 0 ; i < ft_strlen(data->term.line.buf) - ft_strlen(data->history.original_line) ; i++)
		//	{
		//		key_delete_test(data);
		//		write_stored_dont_move(&data->term, data->term.line.i, data->history.original_line, data->term.line.next);
		//	}
		//}
		history = up_history(data->history.original_line, data);
		if (!history)
			return (T_UP);
		if (data->history.original_line)
			history = &history[ft_strlen(data->history.original_line)];
		data->term.line.size = ft_strlen(history);
		data->term.line.next = ft_strlen(history);
		data->term.line.i = ft_strlen(history);
		write(0, history, ft_strlen(history));
		data->term.line.buf = history;
	}
	return (T_UP);
}

int	key_down(t_data *data)
{
	char	*history;

	if (data->term.tab.is_on)
		return (arrow_keys_tab(data, DOWN));
	else
	{
		history = down_history(data->history.original_line, data); //! faire la correspondance avec data->history.original_line
		if (!history)
			return (DOWN);
		data->term.line.size = ft_strlen(history);
		data->term.line.next = ft_strlen(history);
		data->term.line.i = ft_strlen(history);
		write(0, history, ft_strlen(history));
	}
	return (DOWN);
}

int	key_right(t_data *data)
{
	if (data->term.tab.is_on)
		return (arrow_keys_tab(data, RIGHT));
	if (!data->term.line.next)
		return (RIGHT);
	if (data->term.curs.c != data->term.caps.cols)
		write(data->term.fd, data->term.caps.right.cap,
			data->term.caps.right.len);
	else
		move_down(&data->term, 0);
	data->term.line.i++;
	data->term.line.next--;
	update_position(&data->term, RIGHT);
	return (RIGHT);
}

int	key_left(t_data *data)
{
	if (data->term.tab.is_on)
		return (arrow_keys_tab(data, LEFT));
	if (!data->term.line.i)
		return (LEFT);
	if (data->term.curs.c != 1)
		write(data->term.fd, data->term.caps.left.cap,
			data->term.caps.left.len);
	else
		move_up(data, 1);
	data->term.line.i--;
	data->term.line.next++;
	update_position(&data->term, LEFT);
	return (LEFT);
}
