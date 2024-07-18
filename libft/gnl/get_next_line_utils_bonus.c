/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:55:39 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/29 00:03:51 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*free_n(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

char	thereis_nl(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			return (1);
	return (0);
}

size_t	ft_strlenc(const char *str, char c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	else if (c == '\0')
	{
		while (str[i])
			i++;
		return (i);
	}
	while (str[i])
		if (str[i++] == c)
			return (i);
	return (i);
}

char	*ft_strdup_gnl(const char *s)
{
	char	*ret;
	size_t	alloc_size;
	size_t	i;

	alloc_size = ft_strlenc(s, '\0');
	ret = (char *)malloc(sizeof(char) * (alloc_size + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (s[++i])
		ret[i] = s[i];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*ret;
	int		size1;
	int		size2;
	int		i;
	int		n;

	if (!s1)
		return (ft_strdup_gnl(s2));
	if (!s2)
		return (NULL);
	size1 = ft_strlenc(s1, '\0');
	size2 = ft_strlenc(s2, '\0');
	ret = (char *)malloc(sizeof(char) * (size1 + size2 + 1));
	if (!ret)
		return (NULL);
	i = 0;
	n = 0;
	while (s1[i])
		ret[n++] = s1[i++];
	i = 0;
	while (s2[i])
		ret[n++] = s2[i++];
	ret[n] = '\0';
	free(s1);
	return (ret);
}
