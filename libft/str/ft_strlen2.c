/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:09:48 by bama              #+#    #+#             */
/*   Updated: 2024/08/02 20:36:43 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Nombre de string dans le tableau
size_t	ft_strlen2(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

// Nombre total de caractères dans le tableau de strings
size_t	ft_strslen(char **strs)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j++])
			len++;
		i++;
	}
	return (len);
}
