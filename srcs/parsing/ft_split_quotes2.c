/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:32 by ymanchon          #+#    #+#             */
/*   Updated: 2024/08/04 17:10:36 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_squote(const char *str, size_t *i, t_data *data);
int	parse_dquote(const char *str, size_t *i, t_data *data);

int	check_quotes(char c, int *quote_type, t_data *data)
{
	(void)data;
	if (c == '\'')
		*quote_type = 1;
	else if (c == '"')
		*quote_type = 2;
	return (*quote_type);
}

int	parse_quotes(const char *str, int quote_type, size_t *i,
	t_data *data)
{
	if (quote_type == 1)
		return (parse_squote(str, i, data));
	else if (quote_type == 2)
		return (parse_dquote(str, i, data));
	return (0);
}

int	parse_squote(const char *str, size_t *i, t_data *data)
{
	int	passed;

	passed = 0;
	while (str[*i])
	{
		if ((str[*i] == '\'' || passed) && (!str[*i + 1] || str[*i + 1] == ' '))
			return (1);
		else if (str[*i] == '\'' && !passed)
			passed = 1;
		(*i)++;
	}
	data->_errcode = SQUOTE_MISSING;
	return (SQUOTE_MISSING);
}

/*
		Bon"jour mec MOUAH"AHAHH "why are you raging ??" "" A"urevoir "
*/

int	parse_dquote(const char *str, size_t *i, t_data *data)
{
	int	passed;

	passed = 0;
	while (str[*i])
	{
		if ((str[*i] == '"' || passed) && (!str[*i + 1] || str[*i + 1] == ' '))
			return (1);
		else if (str[*i] == '"' && !passed)
			passed = 1;
		(*i)++;
	}
	data->_errcode = DQUOTE_MISSING;
	return (DQUOTE_MISSING);
}

size_t	ft_count_words_quotes(const char *s)
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
		if (((s[i] == '"' || s[i] == '\'')&& ((i != 0 && (is_sep(s[i - 1]) || s[i - 1] == '\'' || s[i - 1] == '"')) || i == 0)) && (squote | dquote))
			words++;
		else if (((i > 0 && is_sep(s[i - 1])) || i == 0) && !is_sep(s[i]) && (squote == 0 && dquote == 0))
			words++;
	}
	return (words);
}
