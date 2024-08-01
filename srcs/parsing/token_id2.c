/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_id2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:17:54 by bama              #+#    #+#             */
/*   Updated: 2024/07/31 14:07:13 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static void	set_type_redirect(t_token **tok,
					t_e_type chevron, t_e_type file)
{
	(*tok)->type = chevron;
	(*tok)->next->type = file;
}

void	detect_redirect_type(t_token **tok)
{
	if (!ft_strcmp((*tok)->value, "<"))
		set_type_redirect(tok, Redirect, Infile);
	else if (!ft_strcmp((*tok)->value, ">"))
		set_type_redirect(tok, Redirect, Outfile);
	else if (!ft_strcmp((*tok)->value, ">>"))
		set_type_redirect(tok, RedirectAppend, Outfile);
	else if (!ft_strcmp((*tok)->value, "<<"))
		set_type_redirect(tok, Redirect, HereDoc);
	else if (!ft_strcmp((*tok)->value, "2>"))
		set_type_redirect(tok, Redirect, Errfile);
}

t_token	*ret_last_token(t_token *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return (tokens);
}

// Après la "review tokenisation" il faut remettre
// certains Tokens en tant que 'Command' car ils ont
// été remplacé par 'Redirect', 'RedirectAPPEND' ou encore
// 'HereDoc' suite à leur détection ...
void	reset_commandtype(t_token **root)
{
	t_token	*tmp;
	t_token	*cmd;

	tmp = *root;
	cmd = *root;
	while (tmp)
	{
		while (tmp && !is_sep_toktype(*tmp))
		{
			if (tmp->type != Redirect && tmp->type != RedirectAppend
				&& tmp->type != HereDoc && tmp->type != Infile
				&& tmp->type != Outfile && tmp->type != Command)
				tmp->type = Command;
			if (tmp->type == Command)
				break ;
			tmp = tmp->next;
		}
		cmd = tok_next_cmd(cmd);
		tmp = cmd;
	}
}
