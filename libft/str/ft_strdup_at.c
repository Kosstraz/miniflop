/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:03:52 by bama              #+#    #+#             */
/*   Updated: 2024/08/08 22:16:51 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_at(const char *str, ssize_t start, ssize_t end)
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

char	*ft_strldup_at(const char *str, ssize_t start, ssize_t end)
{
	char	*ret;

	ret = ft_strdup_at(str, start, end);
	free((char *)str);
	return (ret);
}
