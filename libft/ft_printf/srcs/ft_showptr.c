/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_showptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:09:28 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/26 20:37:18 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_printf.h"

char	*ft_adth(const void *ptr, const char *base)
{
	char			*res;
	unsigned long	i;
	unsigned long	n;

	if (!ptr)
		return (NULL);
	n = (unsigned long)ptr;
	res = (char *)malloc(sizeof(long) * 2 + 2 + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (n > 0)
	{
		res[i++] = base[n % 16];
		n /= 16;
	}
	res[i + 2] = '\0';
	res[i + 1] = '0';
	res[i++] = 'x';
	ft_swapchr(&res, i);
	return (res);
}
