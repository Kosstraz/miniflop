/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handle_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:15:55 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/28 16:42:26 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_printf.h"

char	is_lformat(char c)
{
	int	i;

	i = 0;
	while (LFORMAT[i])
		if (c == LFORMAT[i++])
			return (1);
	return (0);
}

char	is_flag(char c)
{
	int	i;

	i = 0;
	while (__FLAG_[i])
		if (c == __FLAG_[i++])
			return (1);
	return (0);
}

int	ft_write_loop(char c, int *count)
{
	int	i;
	int	ret;

	i = *count;
	ret = 0;
	while (i-- > 0)
		ret += ft_putchar(c);
	*count -= ret;
	return (ret);
}

int	ft_printf_parse_bonus(const char *msg, int *i, va_list *args)
{
	t_flags_info	finfo;
	int				tmp;

	tmp = *i;
	init_flag(&finfo);
	finfo.width = ft_atoi(&msg[*i]);
	while (msg[*i])
	{
		if (is_flag(msg[*i]))
			add_flag(&finfo, msg[*i]);
		else if (is_lformat(msg[*i]))
			return (ft_printf_handle_flags(msg[*i], finfo, args));
		else if (finfo.width >= 0 && !is_digit(msg[*i]))
			return (*i = tmp - 1, 0);
		else if (is_digit(msg[*i]) && !is_digit(msg[*i + 1])
			&& !is_lformat(msg[*i + 1]))
			return (*i = tmp - 1, 0);
		(*i)++;
	}
	return (0);
}

int	ft_printf_handle_flags(char c, t_flags_info finfo, va_list *args)
{
	int		count;
	int		va_int;
	va_list	cpy;

	count = 0;
	va_copy(cpy, *args);
	if (c == 'd' || c == 'i')
		va_int = va_arg(cpy, int);
	if (finfo.width > 0)
	{
		if (c == 'd' || c == 'i')
			finfo.width -= ft_intlen(va_int);
		else if (c == 'u')
			finfo.width -= ft_uintlen(va_arg(cpy, unsigned int));
		if (finfo.width > 0)
			count += ft_write_loop(' ', &finfo.width);
	}
	if ((c == 'x' || c == 'X') && finfo.diez && va_arg(cpy, int))
		return (ft_putchar('0'), ft_putchar(c), 2);
	else if ((c == 'd' || c == 'i') && finfo.space && va_int >= 0
		&& !finfo.plus && finfo.width <= 0)
		count += ft_putchar(' ');
	else if ((c == 'd' || c == 'i') && finfo.plus && va_int >= 0)
		count += ft_putchar('+');
	return (count);
}
