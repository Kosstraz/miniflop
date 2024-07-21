/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wildcards2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:22:07 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 21:33:22 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_wildcard_checking(char **pre_, char **post_, char *word,
		size_t wc_at)
{
	*pre_ = NULL;
	*post_ = NULL;
	if (wc_at != 0)
		*pre_ = ft_strdup_at(word, 0, wc_at);
	if (wc_at + 1 != ft_strlen(word))
		*post_ = ft_strdup_at(word, wc_at + 1,
			ft_strlen(word));
}

void	finish_wildcard_checking(char *pre_, char *post_, char *allfiles,
		const char *word)
{
	if (!allfiles)
		printf(NO_MATCH_FOUND_ERROR, word);
	free(pre_);
	free(post_);
	free(allfiles);
}