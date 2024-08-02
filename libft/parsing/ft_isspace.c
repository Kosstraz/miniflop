/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:40:22 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/28 23:17:58 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_isspace(const char *s, size_t *start)
{
	size_t	i;

	i = *start;
	while (s[*start]
		&& ((s[*start] >= 9 && s[*start] <= 13) || s[*start] == ' '))
		(*start)++;
	return (i);
}
