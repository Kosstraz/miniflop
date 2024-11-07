/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strisdigits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:03:13 by bama              #+#    #+#             */
/*   Updated: 2024/11/06 17:33:02 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 0 : no only digits
// 1 : only digits
char	strisdigits(const char *str)
{
	size_t	i;

	i = 0ULL;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}
