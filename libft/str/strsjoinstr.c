/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsjoinstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:01:28 by bama              #+#    #+#             */
/*   Updated: 2024/08/08 22:40:27 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	strsjoinstr(char ***strs, char *str)
{
	size_t	i;
	char	**new;

	i = 0;
	while ((*strs)[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return ;
	i = 0;
	while ((*strs)[i])
	{
		new[i] = ft_strdup((*strs)[i]);
		i++;
	}
	new[i++] = ft_strdup(str);
	new[i] = NULL;
	*strs = new;
}

// free (*strs)
void	strsljoinstr(char ***strs, char *str)
{
	size_t	i;
	char	**new;

	i = 0;
	while ((*strs)[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return ;
	i = 0;
	while ((*strs)[i])
	{
		new[i] = (*strs)[i];
		i++;
	}
	new[i++] = ft_strdup(str);
	new[i] = NULL;
	free(*strs);
	*strs = new;
}

void	strsjoinstr_at(char ***strs, char *str, size_t at)
{
	size_t	i;
	size_t	j;
	char	**new;

	i = 0;
	while ((*strs)[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return ;
	i = 0;
	j = 0;
	while ((*strs)[i])
	{
		if (j == at)
			new[j++] = ft_strdup(str);
		else
			new[j++] = ft_strdup((*strs)[i++]);
	}
	if (i == at)
		new[j++] = ft_strdup(str);
	new[j] = NULL;
	*strs = new;
}

// free (*strs)
void	strsljoinstr_at(char ***strs, char *str, size_t at)
{
	size_t	i;
	size_t	j;
	char	**new;

	i = 0;
	while ((*strs)[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return ;
	i = 0;
	j = 0;
	while ((*strs)[i])
	{
		if (j == at)
			new[j++] = ft_strdup(str);
		else
			new[j++] = (*strs)[i++];
	}
	if (i == at)
		new[j++] = ft_strdup(str);
	new[j] = NULL;
	free(*strs);
	*strs = new;
}
