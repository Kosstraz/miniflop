/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:30:03 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/17 15:10:06 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ret;
	unsigned long	i;

	ret = (unsigned char *)s;
	i = 0;
	while (i < n)
		ret[i++] = (unsigned char)c;
	return (s);
}
