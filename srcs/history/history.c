/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:49:48 by bama              #+#    #+#             */
/*   Updated: 2024/08/04 17:07:05 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_history(t_data *data)
{
	(void)data;
	//data->historyfd = open(".miniflop.history",
	//		O_CREAT | O_APPEND | O_RDWR, 0666);
}

static size_t	get_nb_of_line_in_fd(int fd)
{
	(void)fd;
	/*char	*gnl;
	size_t	count;

	count = 0;
	gnl = get_next_line(fd);
	while (gnl)
	{
		count++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	return (count);*/
	return (0);
}

// Obtenir la n-ième dernière ligne d'un fichier
// Si n=0 la dernière ligne sera retournée
// Si n=3 la 3ème avant dernière ligne sera retournée
// Si n>[contenu du fd] la première ligne sera tjrs retournée
void	ft_ntail(int fd, int n)
{
	(void)fd;
	(void)n;
	(void)get_nb_of_line_in_fd(fd);
	/*char	*ret;
	char	*gnl;
	size_t	i;
	size_t	size;

	size = get_nb_of_line_in_fd(fd);
	gnl = get_next_line(fd);
	if (n + 1 > size)
		return (gnl);
	i = 0;
	while (gnl && i < size - n)
	{
		i++;
		free(gnl);
		gnl = get_next_line(fd);
	}
	return (gnl);*/
}
