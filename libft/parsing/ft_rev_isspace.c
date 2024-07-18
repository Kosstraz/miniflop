/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_isspace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:40:22 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/28 23:18:15 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_rev_isspace(const char *s, ssize_t size)
{
	if (size == 0)
		size = ft_strlen(s);
	while (size >= 0
		&& ((s[size] >= 9 && s[size] <= 13) || s[size] == ' '))
		size--;
	return (size - 1);
}
