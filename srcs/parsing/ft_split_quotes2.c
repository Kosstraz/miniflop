/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:32 by ymanchon          #+#    #+#             */
/*   Updated: 2024/08/08 02:44:02 by bama             ###   ########.fr       */
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

//else if (str[*i] == '\'' && !passed)
//	passed = 1;
int	parse_squote(const char *str, size_t *i, t_data *data)
{
	char	(*_is_sep_)(char);

	_is_sep_ = data->_is_sep_;
	while (str[*i])
	{
		if (str[*i] == '\'' && (!str[*i + 1] || str[*i + 1] == ' '))
			return (1);
		else if (str[*i] == '\'')
		{
			while (str[*i] && !_is_sep_(str[*i]))
				(*i)++;
			return (1);
		}
		(*i)++;
	}
	data->_errcode = SQUOTE_MISSING;
	return (SQUOTE_MISSING);
}

/*
		Bon"jour mec MOUAH"AHAHH "why are you raging ??" "" A"urevoir "
*/

//else if (str[*i] == '"' && !passed)
//	passed = 1;
int	parse_dquote(const char *str, size_t *i, t_data *data)
{
	char	(*_is_sep_)(char);

	_is_sep_ = data->_is_sep_;
	while (str[*i])
	{
		if (str[*i] == '"' && (!str[*i + 1] || str[*i + 1] == ' '))
			return (1);
		else if (str[*i] == '"')
		{
			while (str[*i] && !_is_sep_(str[*i]))
				(*i)++;
			return (1);
		}
		(*i)++;
	}
	data->_errcode = DQUOTE_MISSING;
	return (DQUOTE_MISSING);
}

size_t	ft_count_words_quotes(const char *s, t_data *data)
{
	size_t	words;
	size_t	i;
	char	quote_status;
	char	(*_is_sep_)(char);

	_is_sep_ = data->_is_sep_;
	quote_status = 0;
	words = 0;
	i = 0;
	while (s[i])
	{
		check_quote_status(s[i], &quote_status);
		if (!_is_sep_(s[i]) && (_is_sep_(s[i + 1]) && !quote_status))
			words++;
		i++;
	}
	return (words);
}
