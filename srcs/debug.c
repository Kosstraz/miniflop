/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:51:01 by bama              #+#    #+#             */
/*   Updated: 2024/07/20 00:53:54 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			printf("[REDIRECTION]\t");
		printf("\e[31m$\e[0m%s\e[31m$\e[0m\n", tok->value);
		tok = tok->next;
	}
}
