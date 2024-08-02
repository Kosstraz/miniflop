/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:09:26 by ymanchon          #+#    #+#             */
/*   Updated: 2024/07/18 11:56:34 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_printf.h"

int	ft_strlen2_printf(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putstr(const char *str)
{
	size_t	size;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	else
	{
		size = ft_strlen2_printf(str);
		write(1, str, size);
		return (size);
	}
}

int	ft_puthexa(char *hexa)
{
	size_t	size;

	if (hexa != NULL)
	{
		size = ft_strlen2_printf(hexa);
		ft_putstr(hexa);
		free(hexa);
		return (size);
	}
	else
	{
		ft_putstr("(nil)");
		return (5);
	}
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr(int n, int len)
{
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		n = -n;
		len += ft_putchar('-');
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, len);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}
