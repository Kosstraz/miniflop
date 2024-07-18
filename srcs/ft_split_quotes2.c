/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:32 by ymanchon          #+#    #+#             */
/*   Updated: 2024/07/18 16:34:20 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_squote(const char *str, size_t *i, size_t *old);
int	parse_dquote(const char *str, size_t *i, size_t *old);

int	check_quotes(char c, int *quote_type)
{
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	if (c == '\'')
		squote = 1;
	else if (c == '"')
		dquote = 2;
	*quote_type = dquote | squote;
	return (dquote | squote);
}

int	parse_quotes(const char *str, int quote_type, size_t *i, size_t *old)
{
	if (quote_type == 1)
		return (parse_squote(str, i, old));
	else if (quote_type == 2)
		return (parse_dquote(str, i, old));
	errcode = ERROR;
	return (ERROR);
}

int	parse_squote(const char *str, size_t *i, size_t *old)
{
	*old = ++(*i);
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
	*old = ++(*i);
	while (str[*i])
	{
		if (str[*i] == '"')
			return (1);
		(*i)++;
	}
	errcode = DQUOTE_MISSING;
	return (DQUOTE_MISSING);
}
