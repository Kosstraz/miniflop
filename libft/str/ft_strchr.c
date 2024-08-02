/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:35 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/23 13:37:57 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, const char c)
{
	unsigned long	i;

	i = 0;
	if (!str)
		return ((void *)0);
	while (str[i])
		if (str[i++] == c)
			return ((char *)&(str[i - 1]));
	if (c == 0)
		return ((char *)&(str[i]));
	return ((char *)0);
}
