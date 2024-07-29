/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_add_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:14:13 by bama              #+#    #+#             */
/*   Updated: 2024/07/29 18:42:51 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Ajouter tous les str de 'strs' à la fin de 'str'
// Entre chaque ajout, un séparateur 'sep' est mis
char	*str_add_strs(char *str, char **strs, char sep)
{
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	new_size;
	char	*ret;

	size = ft_strlen(str);
	new_size = size + ft_strslen(strs) + ft_strlen2(strs);
	ret = (char *)malloc(sizeof(char) * (new_size + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, size);
	i = size;
	ret[i++] = sep;
	j = 0;
	while (strs[j] && i < new_size)
	{
		size = ft_strlen(strs[j]);
		ft_strlcpy(&ret[i], strs[j], size);
		i += size;
		ret[i++] = sep;
		j++;
	}
	ret[new_size] = 0;
	return (ret);
}

// 'str' sera free'd
char	*str_add_strs_free(char *str, char **strs, char sep, char last_sep)
{
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	new_size;
	char	*ret;

	size = ft_strlen(str);
	new_size = size + ft_strslen(strs) + ft_strlen2(strs);
	ret = (char *)malloc(sizeof(char) * (new_size + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, size + 1);
	free(str);
	i = size;
	ret[i++] = last_sep;
	j = 0;
	while (strs[j] && i < new_size)
	{
		size = ft_strlen(strs[j]);
		ft_strlcpy(&ret[i], strs[j++], size + 1);
		i += size;
		ret[i++] = sep;
	}
	ret[new_size] = 0;
	return (ret);
}
