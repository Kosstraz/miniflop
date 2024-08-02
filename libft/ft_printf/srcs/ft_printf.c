/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:09:31 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/13 17:14:09 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_printf.h"

static int	ft_printf_handle(const char *msg, int *i, va_list *args)
{
	size_t			count;
	char			c;

	count = 0;
	++(*i);
	count += ft_printf_parse_bonus(msg, i, args);
	c = msg[*i];
	if (c == 'x' || c == 'X')
		count += ft_puthexa(ft_ith(va_arg(*args, int), c));
	else if (c == 'i' || c == 'd')
		count += ft_putnbr(va_arg(*args, int), 0);
	else if (c == 'c')
		count += ft_putchar((char)va_arg(*args, int));
	else if (c == 'u')
		count += ft_putunbr(va_arg(*args, unsigned int), 0);
	else if (c == 's')
		count += ft_putstr(va_arg(*args, char *));
	else if (c == 'p')
		count += ft_puthexa(ft_adth(va_arg(*args, void *), "0123456789abcdef"));
	else
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *msg, ...)
{
	int			i;
	int			chrs;
	va_list		args;

	if (!msg)
		return (-1);
	va_start(args, msg);
	chrs = 0;
	i = 0;
	while (msg[i])
	{
		if (msg[i] != '%')
			chrs += ft_putchar(msg[i]);
		else
			chrs += ft_printf_handle(msg, &i, &args);
		i++;
	}
	va_end(args);
	return (chrs);
}
