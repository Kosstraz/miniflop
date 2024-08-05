/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:09:44 by bama              #+#    #+#             */
/*   Updated: 2024/08/05 22:18:51 by bama             ###   ########.fr       */
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
				|| !ft_strcmp(tok->value, "2>")
				|| !ft_strcmp(tok->value, "2>>"))
			{
				if (!tok->next || (tok->next && is_sep_toktype(*(tok->next))))
					write(1, PARSE_ERROR_T, PARSE_ERROR_SIZE);
				else if (tok->next)
					detect_redirect_type(&tok);
			}
			else if (!ft_strcmp(tok->value, "(") || !ft_strcmp(tok->value, ")"))
				tok->type = Subshell;
		}
		tok = tok->next;
	}
	reset_commandtype(tokens);
	tok_set_null_to_arg(tokens);
}

// Cherche le type de token auquel correspond le mot splitté
void	check_e_type(t_token **prev, const char *word, int i)
{
	enum e_type	type;

	type = Null;
	if (i == 0 || (*prev)->type == Pipe
		|| (*prev)->type == And || (*prev)->type == Or)
		type = Command;
	else if (ft_strlen(word) == 1)
	{
		if (word[0] == '|')
			type = Pipe;
		else if (word[0] == '(' || word[0] == ')')
			type = Subshell;
	}
	else if (ft_strlen(word) == 2)
	{
		if (word[0] == '&' && word[1] == '&')
			type = And;
		else if (word[0] == '|' && word[1] == '|')
			type = Or;
	}
	if (i != 0
		&& (((*prev)->type == Command || (*prev)->type == Argument)
			&& type == Null))
		type = Argument;
	(*prev)->next->type = type;
}

void	free_tokens(t_token **root)
{
	t_token	*tmp;

	if (root)
	{
		while (*root)
		{
			free((char *)(*root)->value);
			(*root)->value = NULL;
			tmp = (*root)->next;
			free(*root);
			*root = tmp;
		}
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
