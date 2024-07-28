/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_add_strs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:14:13 by bama              #+#    #+#             */
/*   Updated: 2024/07/28 18:16:58 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Ajouter tous les str de 'strs' à la fin de 'str'
// Entre chaque ajout, un séparateur 'sep' est mis
ft_str_add_strs(char *str, char **strs, char sep)
{
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	new_size;

	i = 0;
	j = 0;
	size = ft_strlen(str);
	new_size = size +
}
