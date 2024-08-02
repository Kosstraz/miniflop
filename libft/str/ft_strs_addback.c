/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:02:56 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 16:18:07 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strs_addback(char **strs1, char **strs2)
{
	char	**ret;
	size_t	size;
	size_t	j;
	size_t	i;

	size = ft_strlen2(strs1) + ft_strlen2(strs2);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	size = ft_strlen2(strs1);
	i = 0;
	j = 0;
	while (j < size)
		ret[i++] = strs1[j++];
	size = ft_strlen2(strs2);
	j = 0;
	while (j < size)
		ret[i++] = strs2[j++];
	ret[i] = NULL;
	return (ret);
}

char	**ft_strs_addback_free(char **strs1, char **strs2)
{
	char	**ret;
	size_t	size;
	size_t	j;
	size_t	i;

	size = ft_strlen2(strs1)
		+ ft_strlen2(strs2);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	size = ft_strlen2(strs1);
	i = 0;
	j = 0;
	while (j < size)
		ret[i++] = strs1[j++];
	size = ft_strlen2(strs2);
	j = 0;
	while (j < size)
		ret[i++] = strs2[j++];
	ret[i] = NULL;
	free(strs1);
	free(strs2);
	return (ret);
}
