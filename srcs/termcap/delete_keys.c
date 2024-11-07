/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:21:00 by cachetra          #+#    #+#             */
/*   Updated: 2024/11/07 19:14:08 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete(t_data *data)
{
	if (data->term.curs.c != 1)
		write(data->term.fd, data->term.caps.left.cap, data->term.caps.left.len);
	else
		move_up(data, 1);
	write(data->term.fd, data->term.caps.clear.cap, data->term.caps.clear.len);
}

void	key_backspace(t_data *data)
{
	char	*tmp;

	if (!data->term.line.i)
		return ;
	if (!data->term.line.next)
	{
		delete(data);
		data->term.line.buf[--data->term.line.i] = '\0';
	}
	else
	{
		tmp = (char *)ft_malloc(sizeof(char) * data->term.line.next, data);
		ft_memmove(tmp, &data->term.line.buf[data->term.line.i], data->term.line.next);
		delete(data);
		write_stored_dont_move(&data->term, --data->term.line.i, tmp, data->term.line.next);
		free(tmp);
	}
	data->term.line.size--;
	update_position(&data->term, LEFT);
	update_last(&data->term, 0);
}

void	key_delete(t_data *data)
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
	data->history.original_line = NULL; //!
}
