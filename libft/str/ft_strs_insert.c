/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:21:43 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 16:28:33 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strs_insert(char **strs1, char *str, size_t at)
{
	char	**ret;
	size_t	size;
	size_t	offset;
	size_t	i;

	i = 0;
	size = ft_strlen2(strs1);
	if (at > size + 1)
		at = size + 1;
	ret = (char **)malloc(sizeof(char *) * (size + 2));
	if (!ret)
		return (NULL);
	offset = 0;
	while (i < size + 1)
	{
		if (i == at)
		{
			ret[i++] = str;
			offset++;
		}
		ret[i] = strs1[i + offset];
		i++;
	}
	return (ret);
}
