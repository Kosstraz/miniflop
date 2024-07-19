/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:09:44 by bama              #+#    #+#             */
/*   Updated: 2024/07/20 01:14:37 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
