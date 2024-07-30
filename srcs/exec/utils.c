/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:29:59 by bama              #+#    #+#             */
/*   Updated: 2024/07/30 01:46:59 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tok_next_cmd(t_token *last)
{
	while (last && !is_sep_toktype(*last))
		last = last->next;
	return (last);
}

char	is_a_builtin(const char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO_BLT);
	else if (!ft_strcmp(cmd, "cd"))
		return (CD_BLT);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET_BLT);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT_BLT);
	return (0);
}

size_t	tok_cmdline_size(t_token *cmdline)
{
	size_t	len;

	len = 0;
	while (cmdline && !is_sep_toktype(*cmdline))
	{
		len++;
		cmdline = cmdline->next;
	}
	return (len);
}

char	**tok_to_strs(t_token *cmdline)
{
	char	**ret;
	size_t	size;
	size_t	i;

	if (is_sep_toktype(*cmdline))
		cmdline = cmdline->next;
	size = tok_cmdline_size(cmdline);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i++] = (char *)cmdline->value;
		cmdline = cmdline->next;
	}
	ret[i] = NULL;
	return (ret);
}
