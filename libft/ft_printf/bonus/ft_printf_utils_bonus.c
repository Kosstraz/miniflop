/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:33:37 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/12 20:27:44 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_printf.h"

#define BONUS_FILE

static int	ft_isspace_printf(const char *str)
{
	int	i;

	i = 0;
	while (is_flag(str[i]))
		i++;
	return (i);
}

static int	ft_is_negative(const char *str, int *i)
{
	if (str[*i] == '+' || str[*i] == '-')
		if (str[(*i)++] == '-')
			return (-1);
	return (1);
}

int	ft_atoi_printf(const char *str)
{
	int	ret;
	int	i;

	if (!str)
		return (0);
	ret = 0;
	i = ft_isspace_printf(str);
	ft_is_negative(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
		ret = ret * 10 + (str[i++] - '0');
	return (ret);
}

void	skip_digits(const char *msg, int *i)
{
	while (msg[*i] && is_lformat(msg[*i + 1]))
		(*i)++;
}

char	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
