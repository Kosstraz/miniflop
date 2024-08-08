/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:53:55 by bama              #+#    #+#             */
/*   Updated: 2024/08/07 02:27:39 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cat(char *filepath, int oflags, int mode)
{
	char	*contant;
	char	c;
	int		fd;
	size_t	size;

	size = 0;
	fd = open(filepath, oflags, mode);
	while (read(fd, &c, 1) > 0)
		size++;
	close(fd);
	fd = open(filepath, oflags, mode);
	contant = (char *)malloc(sizeof(char) * (size + 1));
	if (!contant)
		return (NULL);
	read(fd, contant, size);
	contant[size] = 0;
	close(fd);
	return (contant);
}
