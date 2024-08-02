/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_add_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:21:43 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 20:14:01 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strs_add_at(char **strs1, char **strs2, size_t at, char erase)
{
	char	**ret;
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_strlen2(strs1) + ft_strlen2(strs2);
	if (erase)
		size--;
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < at)
		ret[i++] = strs1[j++];
	j = 0;
	size = ft_strlen2(strs2);
	while (j < size)
		ret[i++] = strs2[j++];
	size = ft_strlen2(strs1);
	if (erase)
	{
		free(strs1[at]);
		at++;
	}
	while (at < size)
		ret[i++] = strs1[at++];
	ret[i] = NULL;
	free(strs1);
	free(strs2);
	return (ret);
}
