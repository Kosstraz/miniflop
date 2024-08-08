/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:29:54 by bama              #+#    #+#             */
/*   Updated: 2024/08/07 17:05:11 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  commandword_len
static size_t	cwlen(const char *word)
{
	char	quote_status;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	quote_status = 0;
	while (word[i])
	{
		check_quote_status(word[i], &quote_status);
		if ((word[i] != '\'' && word[i] != '"')
			|| ((quote_status == 1 && word[i] != '\'')
				|| (quote_status == 2 && word[i] != '"')))
			len++;
		i++;
	}
	return (len);
}

void	remquotes(char **new, char *src)
{
	size_t	i;
	size_t	j;
	char	quote_status;

	i = 0;
	j = 0;
	quote_status = 0;
	while (src[i])
	{
		check_quote_status(src[i], &quote_status);
		if ((src[i] != '\'' && src[i] != '"')
			|| ((quote_status == 1 && src[i] != '\'')
				|| (quote_status == 2 && src[i] != '"')))
			(*new)[j++] = src[i];
		i++;
	}
	(*new)[j] = '\0';
}

void	remove_useless_quotes(t_token **root, t_data *data)
{
	char	*tmp;
	t_token	*tok;
	size_t	size;

	tok = *root;
	while (tok)
	{
		size = cwlen(tok->value);
		tmp = (char *)tok->value;
		tok->value = (const char *)malloc(sizeof(const char) * (size + 1));
		if (!tok->value)
			exit_shell(NULL, data, 0);
		if (size > 0)
			remquotes((char **)&tok->value, tmp);
		else
			ft_memset((char *)tok->value, '\0', 1);
		free(tmp);
		tok = tok->next;
	}
}

size_t	cwlen_joker(const char *word)
{
	char	quote_status;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	quote_status = 0;
	while (word[i] && !(!quote_status && word[i] == '*'))
	{
		check_quote_status(word[i], &quote_status);
		if ((word[i] != '\'' && word[i] != '"')
			|| ((quote_status == 1 && word[i] != '\'')
				|| (quote_status == 2 && word[i] != '"')))
			len++;
		i++;
	}
	return (len);
}

void	remquotes_joker(char **new, char *src)
{
	size_t	i;
	size_t	j;
	char	quote_status;

	i = 0;
	j = 0;
	quote_status = 0;
	while (src[i] && !(!quote_status && src[i] == '*'))
	{
		check_quote_status(src[i], &quote_status);
		if ((src[i] != '\'' && src[i] != '"')
			|| ((quote_status == 1 && src[i] != '\'')
				|| (quote_status == 2 && src[i] != '"')))
			(*new)[j++] = src[i];
		i++;
	}
	(*new)[j] = '\0';
}

