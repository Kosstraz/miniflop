/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:20:43 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/07 21:38:53 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_term(t_data *data)
{
	free(data->term.line.buf);
	free(data->term.tab.ref);
	free(data->term.tab.dir);
}

void	kill_term(t_data *data)
{
	if (data->term.state == RAW)
		term_reset(data);
	free_term(data);
}

void	term_reset(t_data *data)
{
	int	log;

	data->term.state = CANON;
	log = tcsetattr(data->term.fd, TCSANOW, &data->term.og);
	if (log)
		exit_shell("\e[1;31mtcsetattr\e[0m", data, EXIT_FAILURE);
}

int	ft_read(int fd, char *buf, int size, t_data *data)
{
	int	br;

	br = read(fd, buf, size);
	if (br == -1)
		exit_shell("\e[1;31mread\e[0m", data, EXIT_FAILURE);
	return (br);
}

void	*ft_malloc(size_t size, t_data *data)
{
	void	*new;

	new = malloc(size);
	if (!new)
		exit_shell("\e[1;31mmalloc\e[0m", data, EXIT_FAILURE);
	return (new);
}

void	*ft_realloc(void *ptr, size_t sze, t_data *data)
{
	size_t	s;
	void	*new;

	new = malloc(sze);
	if (!new)
		exit_shell("\e[1;31mmalloc\e[0m", data, EXIT_FAILURE);
	s = ft_strlen((char *)ptr);
	ft_memmove(new, ptr, s);
	free(ptr);
	return (new);
}
