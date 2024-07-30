/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_id2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:17:54 by bama              #+#    #+#             */
/*   Updated: 2024/07/29 23:30:44 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	detect_redirect_type(t_token **tok)
{
	if (!ft_strcmp((*tok)->value, "<"))
	{
		(*tok)->type = Redirect;
		(*tok)->next->type = Infile;
	}
	else if (!ft_strcmp((*tok)->value, ">"))
	{
		(*tok)->type = Redirect;
		(*tok)->next->type = Outfile;
	}
	else if (!ft_strcmp((*tok)->value, ">>"))
	{
		(*tok)->type = RedirectAppend;
		(*tok)->next->type = Outfile;
	}
	else if (!ft_strcmp((*tok)->value, "<<"))
	{
		(*tok)->type = Redirect;
		(*tok)->next->type = HereDoc;
	}
}

t_token	*ret_last_token(t_token *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return (tokens);
}
