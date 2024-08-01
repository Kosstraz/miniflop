/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:20:43 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/01 13:59:58 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_term(t_data *data)
{
	if (data->term.state == RAW)
		term_reset(data);
	if (data->term.line.buf)
		free(data->term.line.buf);
}

void	term_reset(t_data *data)
{
	int	log;

	log = tcsetattr(data->term.fd, TCSANOW, &data->term.og);
	if (log)
		free_shell(data);
	data->term.state = ORIGINAL;
}

void	*ft_malloc(size_t size, t_data *data)
{
	void	*new;

	new = malloc(size);
	if (!new)
		free_shell(data);
	return (new);
}

void	*ft_realloc(void *ptr, size_t sze, t_data *data)
{
	size_t	s;
	void	*new;

	new = malloc(sze);
	if (!new)
		free_shell(data);
	s = ft_strlen((char *)ptr);
	ft_memmove(new, ptr, s);
	free(ptr);
	return (new);
}
