/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:32 by ymanchon          #+#    #+#             */
/*   Updated: 2024/07/19 18:21:35 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**/int	parse_squote(const char *str, size_t *i, size_t *old);
int	parse_dquote(const char *str, size_t *i, size_t *old);

int	check_quotes(char c, int *quote_type)
{
	if (c == '\'')
		*quote_type = 1;
	else if (c == '"')
		*quote_type = 2;
	return (*quote_type);
}

int	parse_quotes(const char *str, int quote_type, size_t *i, size_t *old)
{
	if (quote_type == 1)
		return (parse_squote(str, i, old));
	else if (quote_type == 2)
		return (parse_dquote(str, i, old));
	return (0);
}

int	parse_squote(const char *str, size_t *i, size_t *old)
{
	while (str[*i])
	{
		if (str[*i] == '\'')
			return (1);
		(*i)++;
	}
	errcode = SQUOTE_MISSING;
	return (SQUOTE_MISSING);
}

int	parse_dquote(const char *str, size_t *i, size_t *old)
{
	while (str[*i])
	{
		if (str[*i] == '"')
			return (1);
		(*i)++;
	}
	errcode = DQUOTE_MISSING;
	return (DQUOTE_MISSING);
}

size_t	ft_count_words_quotes(const char *s, char sep)
{
	size_t	words;
	size_t	i;
	int		squote;
	int		dquote;

	squote = 0;
	dquote = 0;
	words = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' && !squote && !dquote)
			squote = 1;
		else if (s[i] == '\'' && squote)
			squote = 0;
		if (s[i] == '"' && !dquote && !squote)
			dquote = 2;
		else if (s[i] == '"' && dquote)
			dquote = 0;
		if (((s[i] == '"' || s[i] == '\'')&& ((i != 0 && (s[i - 1] == sep || s[i - 1] == '\'' || s[i - 1] == '"')) || i == 0)) && (squote | dquote))
			words++;
		else if (((i > 0 && s[i - 1] == sep) || i == 0) && s[i] != sep && (squote == 0 && dquote == 0))
			words++;
	}
	return (words);
}
