/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:45:21 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/03 17:27:21 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_base(char *base);

int	pos_or_neg(char *nb, int *i);

int	ft_recursive_power(int nb, int power);

int	get_index(char c, char *str);

int	is_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
		if (base[i++] == c)
			return (1);
	return (0);
}

long	ft_atoi_base(char *nb, char *base, int b_len)
{
	int			i;
	int			sign;
	long		ret;

	i = 0;
	ret = 0;
	sign = pos_or_neg(nb, &i);
	while (nb[i])
	{
		if (is_in_base(nb[i], base))
			ret = ret * b_len + get_index(nb[i], base);
		else
			break ;
		i++;
	}
	return (ret * sign);
}

char	*ft_malloc_ret(long nb, int *size, char *base)
{
	char	*ret;

	if (nb < 0)
	{
		ret = malloc(sizeof(char) * (*size + 2));
		if (!ret)
			return (NULL);
		ret[0] = '-';
	}
	else if (nb == 0)
	{
		ret = malloc(sizeof(char) * 2);
		if (!ret)
			return (NULL);
		ret[0] = base[0];
	}
	else
	{
		ret = malloc(sizeof(char) * (*size + 1));
		if (!ret)
			return (NULL);
		(*size)--;
	}
	ret[*size + 1] = '\0';
	return (ret);
}

char	*ft_itoa_base(long nb, char *base, int b_len)
{
	int			i;
	long		n;
	char		*ret;

	i = 0;
	n = nb;
	if (nb < 0)
		nb = -nb;
	while (nb)
	{
		nb /= b_len;
		i++;
	}
	ret = ft_malloc_ret(n, &i, base);
	if (!ret)
		return (NULL);
	if (n < 0)
		n = -n;
	while (i > get_index('-', ret))
	{
		ret[i--] = base[n % b_len];
		n /= b_len;
	}
	return (ret);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int			from_len;
	int			to_len;
	long		temp;
	char		*ret;

	if (check_base(base_from) == 0 || check_base(base_to) == 0)
		return (NULL);
	from_len = ft_strlen(base_from);
	to_len = ft_strlen(base_to);
	temp = ft_atoi_base(nbr, base_from, from_len);
	ret = ft_itoa_base(temp, base_to, to_len);
	return (ret);
}
