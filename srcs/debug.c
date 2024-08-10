/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:51:01 by bama              #+#    #+#             */
/*   Updated: 2024/08/10 00:47:48 by bama             ###   ########.fr       */
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
			printf("joker");
		if (tok->type == Pipe)
			printf("[PIPE]\t\t\t");
		else if (tok->type == And)
			printf("[AND]\t\t\t");
		else if (tok->type == Or)
			printf("[OR]\t\t\t");
		else if (tok->type == Command)
			printf("[COMMAND]\t\t");
		else if (tok->type == Argument)
			printf("[ARGUMENT]\t\t");
		else if (tok->type == RedirectR)
			printf("[REDIRECTIONread]\t");
		else if (tok->type == RedirectW)
			printf("[REDIRECTIONwrite]\t");
		else if (tok->type == RedirectAppend)
			printf("[REDIRECTION (APPEND)]\t");
		else if (tok->type == HereDoc)
			printf("[HERE_DOC]\t\t");
		else if (tok->type == Infile)
			printf("[INFILE]\t\t");
		else if (tok->type == Outfile)
			printf("[OUTFILE]\t\t");
		else if (tok->type == Errfile)
			printf("[ERRFILE]\t\t");
		else if (tok->type == Subshell)
			printf("[SUBSHELL]\t\t");
		else if (tok->type == Null)
			printf("[NULL]\t\t\t");
		printf("\e[31m$\e[0m%s\e[31m$\e[0m\n", tok->value);
		tok = tok->next;
	}
}
