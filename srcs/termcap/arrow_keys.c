/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:01:40 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/08 22:29:31 by bama             ###   ########.fr       */
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

int	key_up(t_data *data)
{
	if (data->term.tab.is_on)
		return (arrow_keys_tab(data, T_UP));
	return (T_UP);
}

int	key_down(t_data *data)
{
	if (data->term.tab.is_on)
		return (arrow_keys_tab(data, DOWN));
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
