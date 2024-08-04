/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:25:41 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/03 00:14:28 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_last(t_term *term, int add)
{
	if (add && term->line.last.c != term->caps.cols)
		term->line.last.c++;
	else if (add && term->line.last.l != term->caps.lines)
	{
		term->line.last.c = 1;
		term->line.last.l++;
	}
	else if (add)
		term->line.last.c = 1;
	else if (term->line.last.c != 1)
		term->line.last.c--;
	else
	{
		term->line.last.c = term->caps.cols;
		term->line.last.l--;
	}
}

void	update_position(t_term *term, int dir)
{
	if (term->curs.c != 1 && dir == LEFT)
		term->curs.c--;
	else if (dir == LEFT)
	{
		term->curs.c = term->caps.cols;
		term->curs.l--;
	}
	else if (term->curs.c != term->caps.cols)
		term->curs.c++;
	else if (term->curs.l != term->caps.lines)
	{
		term->curs.c = 1;
		term->curs.l++;
	}
	else
		term->curs.c = 1;
}

void	get_cursor_position(t_data *data)
{
	int		i;
	int		b_read;
	char	buf[READ];

	i = 1;
	ft_memset(&buf, 0, READ);
	write(STDOUT_FILENO, "\033[6n", 4);
	b_read = ft_read(STDIN_FILENO, buf, READ, data);
	if (!b_read)
		exit_shell("\e[1;31mread\e[0m", data, EXIT_FAILURE);
	buf[b_read] = '\0';
	while (!ft_isdigit(buf[i]))
		i++;
	data->term.curs.l = ft_atoi(&buf[i]);
	while (buf[i] != ';')
		i++;
	data->term.curs.c = ft_atoi(&buf[++i]);
	data->term.line.last.l = data->term.curs.l;
	data->term.line.last.c = data->term.curs.c;
}

void	move_up(t_data *data, int last_col)
{
	char	*cmd;

	write(data->term.fd, data->term.caps.up.cap, data->term.caps.up.len);
	if (!last_col)
		return ;
	cmd = tgoto(data->term.caps.move.cap, data->term.caps.cols, data->term.curs.l - 2);
	if (!cmd)
		exit_shell("\e[1;31mtgoto\e[0m", data, EXIT_FAILURE);
	write(data->term.fd, cmd, ft_strlen(cmd));
}

void	move_down(t_term *term, int first_col)
{
	write(term->fd, term->caps.down.cap, term->caps.down.len);
	if (first_col)
		write(term->fd, term->caps.carriage.cap, term->caps.carriage.len);
}
