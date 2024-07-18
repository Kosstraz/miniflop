/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:30:17 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/23 13:37:57 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_occurence(const char *str, const char *to_find, int i, int limit)
{
	int	j;

	j = 0;
	while (to_find[j])
	{
		if (to_find[j++] != str[i] || i >= limit)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	if (len > ft_strlen(str))
		len = ft_strlen(str);
	while (str[i] && i < len)
	{
		if (find_occurence(str, to_find, i, len) == 1)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
