/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lastword.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:28:10 by bama              #+#    #+#             */
/*   Updated: 2024/08/05 17:33:43 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*lastword(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	if (i == 0)
		return (NULL);
	return (strs[i - 1]);
}

char	*duplastword(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	if (i == 0)
		return (NULL);
	return (ft_strdup(strs[i - 1]));
}
