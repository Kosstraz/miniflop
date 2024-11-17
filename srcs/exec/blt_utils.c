/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:54:41 by bama              #+#    #+#             */
/*   Updated: 2024/11/17 17:01:15 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(char blt_val, t_data *data, t_token *cmdline)
{
	char	**strs;
	int		ret_cmd;

	ret_cmd = -ARG_MAX;
	strs = tok_to_strs(cmdline);
	if (blt_val == ECHO_BLT)
		ret_cmd = ft_echo(strs, data);
	else if (blt_val == CD_BLT)
		ret_cmd = ft_cd(strs, data);
	else if (blt_val == UNSET_BLT)
		ret_cmd = ft_unset(strs, data);
	else if (blt_val == EXIT_BLT)
		ret_cmd = ft_exit(strs, data);
	else if (blt_val == EXPORT_BLT)
		ret_cmd = ft_export(strs, data);
	else if (blt_val == ENV_BLT)
		ret_cmd = ft_env(strs, data);
	else if (blt_val == PWD_BLT)
		ret_cmd = ft_pwd(strs, data);
	else if (blt_val == HDEL_BLT)
		ret_cmd = hdel(strs, data);
	dfree((void **)strs);
	return (ret_cmd);
}

char	is_a_builtin(t_token *cmdline)
{
	char	*cmd;

	while (cmdline && cmdline->type != Command)
		cmdline = cmdline->next;
	cmd = (char *)cmdline->value;
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO_BLT);
	else if (!ft_strcmp(cmd, "cd"))
		return (CD_BLT);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET_BLT);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT_BLT);
	else if (!ft_strcmp(cmd, "export"))
		return (EXPORT_BLT);
	else if (!ft_strcmp(cmd, "env"))
		return (ENV_BLT);
	else if (!ft_strcmp(cmd, "pwd"))
		return (PWD_BLT);
	else if (!ft_strcmp(cmd, "__hdel__"))
		return (HDEL_BLT);
	return (0);
}