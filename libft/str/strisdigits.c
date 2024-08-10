/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strisdigits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:03:13 by bama              #+#    #+#             */
/*   Updated: 2024/08/10 00:04:39 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 0 : no only digits
// 1 : only digits
char	strisdigits(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}
