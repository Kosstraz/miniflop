/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:51 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/23 13:37:57 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, const char c)
{
	char			*ret;
	unsigned long	count;

	count = 0;
	if (!str)
		return ((void *)0);
	ret = (char *)str;
	while (*str)
	{
		if (*(str++) == c)
		{
			ret = (char *)(str - 1);
			count++;
		}
	}
	if (c == 0)
		return ((char *)str);
	if (count == 0)
		return ((void *)0);
	return (ret);
}
