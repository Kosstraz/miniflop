/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:43:30 by ymanchon          #+#    #+#             */
/*   Updated: 2024/08/02 20:43:11 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strslcpy(char **dst, const char **src, size_t siz1)
{
	size_t	i;

	i = 0;
	if (siz1 == 0)
		return (0);
	while (src[i] && i < siz1)
	{
		ft_strlcpy(dst[i], src[i], ft_strlen(src[i]));
		i++;
	}
	dst[i] = NULL;
	return (i * siz1 + 1);
}
