/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:46:19 by cachetra          #+#    #+#             */
/*   Updated: 2024/05/30 18:38:44 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.h"

void	gnl_init(char *s, ssize_t s_size)
{
	ssize_t	i;

	i = 0;
	while (i < s_size)
		s[i++] = 0;
}

ssize_t	gnl_strlen_till(char *str, char c)
{
	ssize_t	i;

	i = 0;
	if (!str)
		return (NOT_FOUND);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (c)
		return (NOT_FOUND);
	return (i);
}

char	*gnl_strndup(char *src, ssize_t n)
{
	ssize_t	i;
	char	*rtn;

	if (!src)
		return (NULL);
	if (n < 0)
		n = gnl_strlen_till(src, 0);
	i = 0;
	rtn = (char *)malloc(sizeof(char) * (n + 1));
	if (!rtn)
		return (NULL);
	while (i < n)
	{
		rtn[i] = src[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	ssize_t	i;
	ssize_t	len;
	char	*rtn;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gnl_strndup(s2, -1));
	if (!s2)
		return (gnl_strndup(s1, -1));
	i = -1;
	len = gnl_strlen_till(s1, 0);
	rtn = (char *)malloc(sizeof(char) * (len + gnl_strlen_till(s2, 0) + 1));
	if (!rtn)
		return (NULL);
	while (s1[++i])
		rtn[i] = s1[i];
	i = -1;
	while (s2[++i])
		rtn[i + len] = s2[i];
	rtn[i + len] = '\0';
	return (rtn);
}

void	gnl_free_null(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
