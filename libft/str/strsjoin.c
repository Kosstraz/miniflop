/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:02:56 by bama              #+#    #+#             */
/*   Updated: 2024/08/08 22:37:24 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**strsjoin(char **strs1, char **strs2)
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
		ret[i++] = ft_strdup(strs1[j++]);
	size = ft_strlen2(strs2);
	j = 0;
	while (j < size)
		ret[i++] = ft_strdup(strs2[j++]);
	ret[i] = NULL;
	return (ret);
}

char	**strsljoin(char **strs1, char **strs2)
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
