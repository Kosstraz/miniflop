/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_isspaceptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:40:22 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/12 20:20:51 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_rev_isspaceptr(const char *s, ssize_t start)
{
	ssize_t	i;

	i = start;
	while (s[start]
		&& ((s[start] >= 9 && s[start] <= 13) || s[start] == ' '))
		start--;
	return (i);
}
