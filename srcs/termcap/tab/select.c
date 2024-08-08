/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:37:03 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/08 22:12:23 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_stored_move(t_term *term, int at, char *mem, int cnt)
{
	int	i;
	int	rem;

	i = at;
	while (term->line.buf[i])
		term->line.buf[i++] = 0;
	ft_memmove(&term->line.buf[at], mem, cnt);
	rem = term->caps.cols - term->curs.c;
	if (rem >= cnt)
		write(term->fd, mem, cnt);
	else
	{
		if (rem)
			write (term->fd, mem, rem);
		write(term->fd, &mem[rem], cnt - rem);
	}
}

static void	move_to_slash(t_data *data)
{
	int	i;
	int	dir_len;

	i = 0;
	if (!data->term.tab.dir)
		return ;
	dir_len = ft_strlen(data->term.tab.dir);
	while (i < dir_len && ft_strncmp(&data->term.tab.dir[i],
		&data->term.line.buf[data->term.line.i], dir_len - i))
		i++;
	if (i == dir_len)
		return ;
	i = dir_len - i;
	while (i--)
	{
		if (data->term.curs.c != data->term.caps.cols)
			write(data->term.fd, data->term.caps.right.cap,
				data->term.caps.right.len);
		else
			move_down(&data->term, 0);
		data->term.line.i++;
	}
}

static void	tab_insert_loop(t_data *data, int ref_len)
{
	move_to_slash(data);
	if (!ref_len)
		return ;
	while (data->term.line.i && !(data->term.line.buf[data->term.line.i]
		== data->term.tab.ref[0] && !ft_strncmp(&data->term.line.buf
			[data->term.line.i], data->term.tab.ref, ref_len)))
		{
			if (data->term.curs.c != 1)
				write(data->term.fd, data->term.caps.left.cap,
					data->term.caps.left.len);
			else
				move_up(data, 1);
			data->term.line.i--;
		}
}

static char	*tab_insert(t_data *data, char *selected, int len)
{
	int		tmp;
	int		ref_len;
	char	*rtn;

	ref_len = ft_strlen(data->term.tab.ref);
	ft_memmove(selected, data->term.tab.files[data->term.tab.pos], len);
	if (data->term.line.size + len >= data->term.line.total)
		resize_line_buffer(data);
	tab_insert_loop(data, ref_len);
	tmp = data->term.line.size - data->term.line.i - ref_len + 1;
	rtn = (char *)ft_malloc(sizeof(char) * tmp, data);
	ft_memmove(rtn, &data->term.line.buf[data->term.line.i + ref_len], tmp);
	write_stored_move(&data->term, data->term.line.i, selected, len);
	data->term.line.i += len;
	len -= ref_len;
	data->term.line.size += len;
	data->term.line.next = data->term.line.size -  data->term.line.i;
	while (len--)
	{
		update_position(&data->term, RIGHT);
		update_last(&data->term, 1);
	}
	return (rtn);
}

void	tab_select(t_data *data, char shortcut)
{
	int		len;
	char	*tmp;
	char	selected[S_CHUNK];

	if (!shortcut)
		tab_clear(data);
	ft_memset(selected, 0, S_CHUNK);
	len = ft_strlen(data->term.tab.files[data->term.tab.pos]);
	tmp = tab_insert(data, selected, len);
	if (tmp[0])
	{
		len = ft_strlen(tmp);
		write_stored_dont_move(&data->term, data->term.line.i, tmp, len);
	}
	free(tmp);
	tab_reset(data, 0);
}
