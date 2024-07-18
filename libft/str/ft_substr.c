/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:55 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/23 13:37:57 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	ssize;
	size_t	i;

	ssize = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > ssize)
		start = ssize;
	if (len > ssize - start)
		len = ssize - start;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}
