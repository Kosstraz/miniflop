/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:11 by ymanchon          #+#    #+#             */
/*   Updated: 2024/08/06 23:34:42 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen_itoa(int n)
{
	int	n_len;

	n_len = 0;
	while (n > 0)
	{
		n_len++;
		n /= 10;
	}
	return (n_len);
}

static char	*ft_itoa_int_min(void)
{
	char	*ret;
	int		n;
	int		n_len;

	ret = (char *)malloc(12);
	if (!ret)
		return ((char *)0);
	ret[0] = '-';
	ret[11] = '\0';
	ret[10] = '8';
	n = 214748364;
	n_len = 9;
	while (n_len >= 1)
	{
		ret[n_len--] = n % 10 + '0';
		n /= 10;
	}
	return (ret);
}

static char	*ft_itoa_zero(void)
{
	char	*ret;

	ret = (char *)malloc(2);
	if (!ret)
		return ((char *)0);
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

static char	*ft_itoa_neg(long n)
{
	char	*ret;
	int		n_len;

	if (n == -2147483648)
		return (ft_itoa_int_min());
	n_len = ft_intlen_itoa(n);
	ret = (char *)malloc(n_len + 2);
	if (!ret)
		return ((char *)0);
	ret[0] = '-';
	ret[n_len + 1] = '\0';
	while (n_len >= 1)
	{
		ret[n_len--] = n % 10 + '0';
		n /= 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		n_len;

	if (n == 0)
		return (ft_itoa_zero());
	if (n < 0)
		return (ft_itoa_neg(-n));
	n_len = ft_intlen_itoa(n);
	ret = (char *)malloc(n_len + 1);
	if (!ret)
		return ((char *)0);
	ret[n_len--] = '\0';
	while (n_len >= 0)
	{
		ret[n_len--] = n % 10 + '0';
		n /= 10;
	}
	return (ret);
}
