/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:51:01 by bama              #+#    #+#             */
/*   Updated: 2024/07/22 22:47:44 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_linked_list(t_env *env)
{
	while (env)
	{
		ft_printf("name: %s\nvalue: %s\n\n", env->name, env->value);
		env = env->next;
	}
}

void	show_token(t_token *tok)
{
	while (tok)
	{
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
		else if (tok->type == Redirect)
			printf("[REDIRECTION]\t\t");
		else if (tok->type == RedirectAppend)
			printf("[REDIRECTION (APPEND)]\t");
		else if (tok->type == HereDoc)
			printf("[HERE_DOC]\t\t");
		else if (tok->type == Infile)
			printf("[INFILE]\t\t");
		else if (tok->type == Outfile)
			printf("[OUTFILE]\t\t");
		printf("\e[31m$\e[0m%s\e[31m$\e[0m\n", tok->value);
		tok = tok->next;
	}
}
