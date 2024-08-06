/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:53:55 by bama              #+#    #+#             */
/*   Updated: 2024/08/07 01:08:42 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cat(int fd)
{
	char	*contant;
	char	c;
	size_t	size;

	size = 0;
	while (read(fd, &c, 1) > 0)
		size++;
	contant = (char *)malloc(sizeof(char) * (size + 1));
	if (!contant)
		return (NULL);
	read(fd, contant, size);
	contant[size] = 0;
	return (contant);
}
