/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printables.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:13:46 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/07 18:07:54 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_stored_dont_move(t_term *term, int at, char *mem, int cnt)
{
	int	i;
	int	rem;

	i = at;
	while (term->line.buf[i])
		term->line.buf[i++] = 0;
	ft_memmove(&term->line.buf[at], mem, cnt);
	write(term->fd, term->caps.save.cap, term->caps.save.len);
	rem = term->caps.cols - term->curs.c;
	if (rem >= cnt)
		write(term->fd, mem, cnt);
	else
	{
		if (rem)
			write (term->fd, mem, rem);
		write(term->fd, &mem[rem], cnt - rem);
	}
	write(term->fd, term->caps.restore.cap, term->caps.restore.len);
}

static void	edge_case_last_line(t_data *data, int c)
{
	char	*tmp;

	tmp = (char *)ft_malloc(sizeof(char) * data->term.line.next, data);
	ft_memmove(tmp, &data->term.line.buf[data->term.line.i], data->term.line.next);
	write(1, &c, 1);
	write(data->term.fd, data->term.caps.save.cap, data->term.caps.save.len);
	update_position(&data->term, RIGHT);
	data->term.line.buf[data->term.line.i++] = c;
	data->term.line.size++;
	write_stored_dont_move(&data->term, data->term.line.i, tmp, data->term.line.next);
	write(data->term.fd, data->term.caps.restore.cap, data->term.caps.restore.len);
	if (data->term.curs.l >= data->term.caps.lines - 1)
		move_up(data, 0);
	free(tmp);
}

static void	edge_case_last_char(t_data *data, int c)
{
	char	*tmp;

	write(data->term.fd, data->term.caps.clear.cap, data->term.caps.clear.len);
	tmp = (char *)ft_malloc(sizeof(char) * data->term.line.next, data);
	ft_memmove(tmp, &data->term.line.buf[data->term.line.i], data->term.line.next);
	write(1, &c, 1);
	update_position(&data->term, RIGHT);
	data->term.line.buf[data->term.line.i++] = c;
	data->term.line.size++;
	move_down(&data->term, 1);
	write_stored_dont_move(&data->term, data->term.line.i, tmp, data->term.line.next);
	free(tmp);
}

static void	insert_char(t_data *data, int c)
{
	char		*tmp;

	if (data->term.curs.c == data->term.caps.cols)
	{
		edge_case_last_char(data, c);
		return ;
	}
	if (data->term.line.last.l == data->term.caps.lines && data->term.line.last.c == 1)
	{
		edge_case_last_line(data, c);
		return ;
	}
	tmp = (char *)ft_malloc(sizeof(char) * data->term.line.next, data);
	ft_memmove(tmp, &data->term.line.buf[data->term.line.i], data->term.line.next);
	write(1, &c, 1);
	update_position(&data->term, RIGHT);
	data->term.line.buf[data->term.line.i++] = c;
	data->term.line.size++;
	write_stored_dont_move(&data->term, data->term.line.i, tmp, data->term.line.next);
	free(tmp);
}

void	print_char(t_data *data, int c)
{
	if (!data->term.line.next)
	{
		write(1, &c, 1);
		data->term.line.buf[data->term.line.i++] = c;
		data->term.line.size++;
		update_position(&data->term, RIGHT);
	}
	else
		insert_char(data, c);
	update_last(&data->term, 1);
}
