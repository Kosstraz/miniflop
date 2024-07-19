/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:51:01 by bama              #+#    #+#             */
/*   Updated: 2024/07/18 18:47:56 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_token(const t_token **tok)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		if (tok[i]->type == Pipe)
			printf("[PIPE]\t\t\t");
		else if (tok[i]->type == And)
			printf("[AND]\t\t\t");
		else if (tok[i]->type == Or)
			printf("[OR]\t\t\t");
		else if (tok[i]->type == Command)
			printf("[COMMAND]\t\t");
		else if (tok[i]->type == Argument)
			printf("[ARGUMENT]\t\t");
		else if (tok[i]->type == Redirect)
			printf("[REDIRECTION]\t");
		printf("\e[31m$\e[0m%s\e[31m$\e[0m\n", tok[i]->value);
		i++;
	}
}
