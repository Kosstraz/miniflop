/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:01:21 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/13 17:14:20 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_count_words(const char *s, char sep)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = -1;
	while (s[++i])
		if (((i > 0 && s[i - 1] == sep) || i == 0) && s[i] != sep)
			words++;
	return (words);
}
