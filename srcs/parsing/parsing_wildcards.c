/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:47:22 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 20:58:26 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_wildcard(char ***splitted, size_t word_at, size_t at)
{
	struct dirent	*dirent;
	DIR				*dir;
	char			*allfiles;
	char			*pre_wildcard;
	char			*post_wildcard;
	char			**wildcard;

	dir = opendir(".");
	dirent = readdir(dir);
	pre_wildcard = NULL;
	post_wildcard = NULL;
	if (at != 0)
		pre_wildcard = ft_strdup_at((*splitted)[word_at], 0, at);
	if (at + 1 != ft_strlen((*splitted)[word_at]))
		post_wildcard = ft_strdup_at((*splitted)[word_at], at + 1, ft_strlen((*splitted)[word_at]));
	allfiles = NULL;
	while (dirent)
	{
		if (((!pre_wildcard && !post_wildcard)
		|| (!ft_strncmp(dirent->d_name, pre_wildcard, ft_strlen(pre_wildcard)) && !post_wildcard)
		|| (!ft_strncmp_rev(dirent->d_name, post_wildcard, ft_strlen(post_wildcard)) && !pre_wildcard)
		|| (!ft_strncmp_rev(dirent->d_name, post_wildcard, ft_strlen(post_wildcard)) && !ft_strncmp(dirent->d_name, pre_wildcard, ft_strlen(pre_wildcard))))
		&& (ft_strcmp(dirent->d_name, ".") && ft_strcmp(dirent->d_name, ".."))
		&& (ft_strncmp(dirent->d_name, ".", 1) || (pre_wildcard && !ft_strncmp(pre_wildcard, ".", 1))))
		{
			allfiles = ft_strsjoin(allfiles, dirent->d_name);
			allfiles = ft_strsjoin(allfiles, " ");
		}
		dirent = readdir(dir);
	}
	free(pre_wildcard);
	free(post_wildcard);
	closedir(dir);
	if (!allfiles)
		return ;
	wildcard = ft_split(allfiles, ' ');
	free(allfiles);
	*splitted = ft_strs_add_at(*splitted, wildcard, word_at, 1);
}

void	place_wildcards(char ***splitted)
{
	char	quote_opened;
	size_t	i;
	size_t	j;

	quote_opened = 0;
	i = 0;
	while ((*splitted)[i])
	{
		j = 0;
		while ((*splitted)[i][j])
		{
			check_quote_status((*splitted)[i][j], &quote_opened);
			if ((*splitted)[i][j] == '*' && !quote_opened)
				handle_wildcard(splitted, i, j);
			j++;
		}
		i++;
	}
}
