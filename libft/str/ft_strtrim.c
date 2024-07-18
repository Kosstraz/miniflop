/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:53 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/23 13:37:57 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_set(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
		if (c == set[i++])
			return (1);
	return (0);
}

static void	skipset(const char *str, const char *set, ssize_t *a, ssize_t *b)
{
	ssize_t	i;
	ssize_t	size;
	char	flag;

	i = 0;
	flag = 0;
	size = ft_strlen(str);
	while (i < size && !flag)
		if (!is_set(str[i++], set))
			flag++;
	*a = i - 1;
	if (!flag)
		*a = 0;
	flag = 0;
	i = size - 1;
	while (i >= 0 && i < size && !flag)
		if (!is_set(str[i--], set))
			flag++;
	*b = i + 2;
	if (!flag)
		*b = size;
}

static char	*strdup_at(const char *str, ssize_t start, ssize_t end)
{
	size_t	i;
	size_t	size;
	char	*ret;

	size = end - start;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = '\0';
	i = 0;
	while (start < end)
		ret[i++] = str[start++];
	return (ret);
}

static char	allocc(const char *str, const char *set)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (!is_set(str[i++], set))
			return (0);
	return (1);
}

char	*ft_strtrim(const char *str, const char *set)
{
	char	*ret;
	ssize_t	s;
	ssize_t	e;

	if (allocc(str, set))
	{
		ret = (char *)malloc(sizeof(char));
		if (!ret)
			return (NULL);
		ret[0] = '\0';
		return (ret);
	}
	skipset(str, set, &s, &e);
	ret = strdup_at(str, s, e);
	if (!ret)
		return (NULL);
	return (ret);
}
