/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:45:59 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/03 17:40:23 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (!base[0] || !base[1])
		return (0);
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	pos_or_neg(char *str, int *i)
{
	int	count;

	count = 0;
	while (str[*i])
	{
		if ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' ')
		{
			if (count)
				break ;
		}
		else if (str[*i] == '-')
			count++;
		else if (str[*i] != '+')
			break ;
		(*i)++;
	}
	if (count % 2 == 1)
		return (-1);
	return (1);
}

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}

int	get_index(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
