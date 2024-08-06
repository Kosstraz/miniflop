/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:48 by ymanchon          #+#    #+#             */
/*   Updated: 2024/08/06 23:42:05 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long	i;

	i = 0;
	if (!s1 || !s2)
		return ((int)((unsigned long)s1 - (unsigned long)s2));
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*
	Parcours les caractères à partir de la fin de la chaîne.
*/
int	ft_strncmp_rev(const char *s1, const char *s2, size_t n)
{
	unsigned long	cpt;
	long			i;
	long			j;

	cpt = 0;
	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while ((i >= 0 && j >= 0) && cpt < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[j])
			return ((unsigned char)s1[i] - (unsigned char)s2[j]);
		i--;
		j--;
		cpt++;
	}
	return (0);
}
