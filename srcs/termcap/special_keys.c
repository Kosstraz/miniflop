/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:24:47 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/06 01:53:51 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//
void	key_tab(t_data *data)
{
	int		n;
	char	*tmp;
	char	*ref;

	n = data->term.curs.l;
	// i = data->term.line.i;
	// while (i > 1 && data->term.line.buf[i] != ' '
	// 	&& data->term.line.buf[i] != '\t')
	// 		i--;
	ref = ft_strrchr((const char *)data->term.line.buf, ' ');
	ft_putendl_fd(ref, 1);
	// if (!tmp)
	// 	ref = ft_strdup(data->term.line.buf);
	// else
	// 	ref = ft_strdup(tmp);
	// if (!ref)
	// 	exit_shell("\e[31mft_strdup\e[0m", data, EXIT_FAILURE);
	write(data->term.fd, data->term.caps.save.cap,
		data->term.caps.save.len);
	while (n++ <= data->term.line.last.l)
		write(data->term.fd, "\n", 1);
	show_dir_contents(".", ref, data);
	write(data->term.fd, data->term.caps.restore.cap,
		data->term.caps.restore.len);
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
