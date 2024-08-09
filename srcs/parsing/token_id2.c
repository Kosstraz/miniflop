/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_id2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:17:54 by bama              #+#    #+#             */
/*   Updated: 2024/08/09 17:58:18 by bama             ###   ########.fr       */
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
		set_type_redirect(tok, RedirectR, Infile);
	else if (!ft_strcmp((*tok)->value, ">"))
		set_type_redirect(tok, RedirectW, Outfile);
	else if (!ft_strcmp((*tok)->value, ">>"))
		set_type_redirect(tok, RedirectAppend, Outfile);
	else if (!ft_strcmp((*tok)->value, "<<"))
		set_type_redirect(tok, RedirectR, HereDoc);
	else if (!ft_strcmp((*tok)->value, "2>"))
		set_type_redirect(tok, RedirectW, Errfile);
	else if (!ft_strcmp((*tok)->value, "2>>"))
		set_type_redirect(tok, RedirectAppend, Errfile);
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
			if (tmp->type == Null)
				tmp->type = Argument;
			if (tmp->type != RedirectR && tmp->type != RedirectW
				&& tmp->type != RedirectAppend
				&& tmp->type != HereDoc && tmp->type != Infile
				&& tmp->type != Outfile && tmp->type != Command
				&& tmp->type != Subshell && tmp->type != Errfile
				&& tmp->type != Comma)
				tmp->type = Command;
			if (tmp->type == Command)
				break ;
			tmp = tmp->next;
		}
		cmd = tok_next_cmd(cmd);
		tmp = cmd;
	}
}

void	tok_set_null_to_arg(t_token **root)
{
	t_token	*tmp;

	tmp = *root;
	while (tmp)
	{
		if (tmp->type == Null)
			tmp->type = Argument;
		tmp = tmp->next;
	}
}
