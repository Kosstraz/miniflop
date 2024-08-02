/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:24:47 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/01 14:01:34 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	key_tab(t_data *data)
{
	if (data)
		write(2, "TAB\n", 4);
}

void	key_up(t_data *data)
{
	if (data)
		write(2, "UP\n", 3);
}

void	key_down(t_data *data)
{
	if (data)
		write(2, "DOWN\n", 5);
}

void	key_right(t_data *data)
{
	if (!data->term.line.next)
		return ;
	if (data->term.curs.c != data->term.caps.cols)
		write(data->term.fd, data->term.caps.right.cap, data->term.caps.right.len);
	else
		move_down(&data->term, 0);
	data->term.line.i++;
	data->term.line.next--;
	update_position(&data->term, RIGHT);
}

void	key_left(t_data *data)
{
	if (!data->term.line.i)
		return ;
	if (data->term.curs.c != 1)
		write(data->term.fd, data->term.caps.left.cap, data->term.caps.left.len);
	else
		move_up(data, 1);
	data->term.line.i--;
	data->term.line.next++;
	update_position(&data->term, LEFT);
}
