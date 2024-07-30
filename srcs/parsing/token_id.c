/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:09:44 by bama              #+#    #+#             */
/*   Updated: 2024/07/30 14:52:33 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	review_tokenid(t_token **tokens)
{
	t_token	*tok;

	tok = *tokens;
	while (tok)
	{
		if (tok->value)
		{
			if (!ft_strcmp(tok->value, "<") || !ft_strcmp(tok->value, ">")
				|| !ft_strcmp(tok->value, ">>")
				|| !ft_strcmp(tok->value, "<<")
				|| (ft_isdigit(tok->value[0])
					&& !ft_strcmp(&tok->value[1], ">")))
			{
				if (!tok->next || (tok->next && is_sep_toktype(*(tok->next))))
					write(1, PARSE_ERROR_T, PARSE_ERROR_SIZE);
				else if (tok->next)
					detect_redirect_type(&tok);
			}
		}
		tok = tok->next;
	}
}

// Cherche le type de token auquel correspond le mot splitté
void	check_e_type(t_token **second, const char *word, int i)
{
	enum e_type	type;

	type = Null;
	if (i == 0 || (*second)->type == Pipe
		|| (*second)->type == And || (*second)->type == Or)
		type = Command;
	else if (ft_strlen(word) == 1)
	{
		if (word[0] == '|')
			type = Pipe;
	}
	else if (ft_strlen(word) == 2)
	{
		if (word[0] == '&' && word[1] == '&')
			type = And;
		else if (word[0] == '|' && word[1] == '|')
			type = Or;
	}
	if (i != 0
		&& (((*second)->type == Command || (*second)->type == Argument)
			&& type == Null))
		type = Argument;
	(*second)->next->type = type;
}

void	free_tokens(t_token **root)
{
	t_token	*tmp;

	while (*root)
	{
		free((char *)(*root)->value);
		(*root)->value = NULL;
		tmp = (*root)->next;
		free(*root);
		*root = tmp;
	}
}

t_token	*last_token(t_token *tokens)
{
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

t_token	*new_token(char *value)
{
	t_token	*ret;

	ret = (t_token *)malloc(sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->type = Null;
	ret->value = value;
	ret->next = NULL;
	return (ret);
}
