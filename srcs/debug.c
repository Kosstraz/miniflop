/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:51:01 by bama              #+#    #+#             */
/*   Updated: 2024/11/13 18:29:10 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

void	show_token(t_token *tok)
{
	while (tok)
	{
		if (tok->joker)
			ft_printf("joker");
		if (tok->type == Pipe)
			ft_printf("[PIPE]\t\t\t");
		else if (tok->type == And)
			ft_printf("[AND]\t\t\t");
		else if (tok->type == Or)
			ft_printf("[OR]\t\t\t");
		else if (tok->type == Command)
			ft_printf("[COMMAND]\t\t");
		else if (tok->type == Argument)
			ft_printf("[ARGUMENT]\t\t");
		else if (tok->type == RedirectR)
			ft_printf("[REDIRECTIONread]\t");
		else if (tok->type == RedirectW)
			ft_printf("[REDIRECTIONwrite]\t");
		else if (tok->type == RedirectAppend)
			ft_printf("[REDIRECTION (APPEND)]\t");
		else if (tok->type == HereDoc)
			ft_printf("[HERE_DOC]\t\t");
		else if (tok->type == Infile)
			ft_printf("[INFILE]\t\t");
		else if (tok->type == Outfile)
			ft_printf("[OUTFILE]\t\t");
		else if (tok->type == Errfile)
			ft_printf("[ERRFILE]\t\t");
		else if (tok->type == Subshell)
			ft_printf("[SUBSHELL]\t\t");
		else if (tok->type == Null)
			ft_printf("[NULL]\t\t\t");
		else if (tok->type == Comma)
			ft_printf("[COMMA]\t\t\t");
		else
			ft_printf("chelou");
		ft_printf("\e[31m$\e[0m%s\e[31m$\e[0m\n", tok->value);
		tok = tok->next;
	}
}
