/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parseerror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:09:41 by bama              #+#    #+#             */
/*   Updated: 2024/11/17 16:12:45 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_parentheses_status(t_token *cmdline,
			int *inc, int *outc)
{
	char	there_is_action;

	there_is_action = FALSE;
	while (cmdline)
	{
		if (cmdline->type == Subshell && !ft_strcmp(cmdline->value, "("))
		{
			++(*inc);
			there_is_action = FALSE;
		}
		else if (cmdline->type == Subshell && !ft_strcmp(cmdline->value, ")"))
		{
			++(*outc);
			if (!there_is_action)
				break ;
		}
		else if (!ft_strcmp(cmdline->value, "()"))
			there_is_action = FALSE;
		else
			there_is_action = TRUE;
		cmdline = cmdline->next;
	}
	return (there_is_action);
}

int	is_there_subshells(t_token *cmdline, t_data *data)
{
	int		inc;
	int		outc;
	char	there_is_action;

	inc = 0;
	outc = 0;
	there_is_action = check_parentheses_status(cmdline, &inc, &outc);
	if (inc != outc)
		data->_errcode = SUBSHELL_MISSING;
	else if (!there_is_action)
		data->_errcode = SUBSHELL_USELESS;
	return (data->_errcode);
}
