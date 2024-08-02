/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:47:22 by bama              #+#    #+#             */
/*   Updated: 2024/07/30 15:05:43 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finish_wildcard_checking(char *pre_, char *post_, char *allfiles,
		const char *word);
void	init_wildcard_checking(char **pre_, char **post_, char *word,
		size_t wc_at);

static char	check_wildcard_protection(char *pre_, char *post_, char *fname)
{
	char	bool_;
	char	bool_dir;

	bool_dir = 
	bool_ = ((!pre_ && !post_)
		|| (!ft_strncmp(fname, pre_, ft_strlen(pre_)) && !post_)
		|| (!ft_strncmp_rev(fname, post_, ft_strlen(post_)) && !pre_)
		|| (!ft_strncmp_rev(fname, post_, ft_strlen(post_))
			&& !ft_strncmp(fname, pre_, ft_strlen(pre_))))
		&& (ft_strcmp(fname, ".") && ft_strcmp(fname, ".."))
		&& (ft_strncmp(fname, ".", 1) || (pre_ && !ft_strncmp(pre_, ".", 1)));
	if (bool_dir)
		return (2);
	else if (bool_)
		return (1);
	return (0);
}

static char	handle_wildcard(char ***splitted, size_t word_at, size_t at)
{
	struct dirent	*dirent;
	DIR				*dir;
	char			*allfiles;
	char			*pre_wc;
	char			*post_wc;
	char			**wildcard;

	dir = opendir(".");
	dirent = readdir(dir);
	init_wildcard_checking(&pre_wc, &post_wc, (*splitted)[word_at], at);
	allfiles = NULL;
	while (dirent)
	{
		if (check_wildcard_protection(pre_wc, post_wc, dirent->d_name))
		{
			allfiles = ft_strsjoin(allfiles, dirent->d_name);
			allfiles = ft_strsjoin(allfiles, " ");
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	if (!allfiles)
		return (finish_wildcard_checking(pre_wc, post_wc, NULL, (*splitted)[word_at]), 0);
	wildcard = ft_split(allfiles, ' ');
	*splitted = ft_strs_add_at(*splitted, wildcard, word_at, 1);
	return (finish_wildcard_checking(pre_wc, post_wc, allfiles, NULL), 1);
}

void	apply_wildcards(char ***splitted)
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
