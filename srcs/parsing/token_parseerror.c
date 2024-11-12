/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parseerror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:09:41 by bama              #+#    #+#             */
/*   Updated: 2024/11/12 16:20:07 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_parentheses_status(t_token *cmdline, t_data *data,
			int *inc, int *outc)
{
	if (!ft_strcmp(cmdline->value, "()"))
	{
		data->_errcode = SUBSHELL_INVALID;
		return (0);
	}
	if (cmdline->type == Subshell)
	{
		if (!ft_strcmp(cmdline->value, "("))
		{
			(*inc)++;
			if (cmdline->next && !ft_strcmp(cmdline->next->value, "("))
			{
				data->_errcode = SUBSHELL_USELESS;
				return (0);
			}
		}
		else if (!ft_strcmp(cmdline->value, ")"))
			(*outc)++;
	}
	return (1);
}

static char	loop_finished_status_tokparseerror(t_data *data,
			int there_is_action, int inc, int outc)
{
	if (inc == outc && there_is_action)
		return (inc);
	if (!there_is_action && inc > 0)
		data->_errcode = SUBSHELL_INVALID;
	else if (inc != outc)
		data->_errcode = SUBSHELL_MISSING;
	return (0);
}

int	is_there_subshells(t_token *cmdline, t_data *data)
{
	int	inc;
	int	outc;
	int	there_is_action;

	inc = 0;
	outc = 0;
	there_is_action = 0;
	while (cmdline)
	{
		if (is_sep_toktype(*cmdline))
		{
			if (!there_is_action)
				break ;
			if (inc == outc)
				return (inc);
		}
		if (inc > 0 && (cmdline->type == Command || is_redirection(cmdline)))
			there_is_action = 1;
		if (!check_parentheses_status(cmdline, data, &inc, &outc))
			return (0);
		cmdline = cmdline->next;
	}
	return (loop_finished_status_tokparseerror(
			data, there_is_action, inc, outc));
}
