/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:09:20 by ymanchon          #+#    #+#             */
/*   Updated: 2024/07/08 19:02:35 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_is_negative(const char *str, size_t *i)
{
	if (str[*i] == '+' || str[*i] == '-')
		if (str[(*i)++] == '-')
			return (-1);
	return (1);
}

float	ft_atof(char *str)
{
	int		big;
	int		precision;
	size_t	i;
	float	ret;

	big = ft_atoi(str);
	ret = (float)big;
	i = 0;
	ft_isspace(str, &i);
	ft_is_negative(str, &i);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i++] != '.')
		return (ret);
	precision = ft_atoi(&str[i]);
	if (precision == 0)
		return (ret);
	i = ft_intlen(precision);
	while (precision)
	{
		ret += (float)((float)(precision % 10) / (float)ft_pow(10, i--));
		precision /= 10;
	}
	i = 0;
	return (ret * ft_is_negative(str, &i));
}
