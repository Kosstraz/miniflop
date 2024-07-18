/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:14:45 by ymanchon          #+#    #+#             */
/*   Updated: 2024/07/07 23:46:25 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, unsigned int n)
{
	char			*ret;
	unsigned long	i;

	ret = (char *)malloc(sizeof(char) * (n + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
