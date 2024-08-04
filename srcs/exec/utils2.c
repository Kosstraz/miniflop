/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:28:31 by bama              #+#    #+#             */
/*   Updated: 2024/08/03 21:44:11 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_execve(char *path, t_token *cmdline, t_data *data)
{
	char	**args;
	char	**env;

	args = tok_to_strs(cmdline);
	env = convert_env(data->env);
	free_data(data);
	free_env(&data->env);
	free_term(data);
	execve((const char *)path,
		(char *const *)args,
		(char *const *)env);
	free(path);
	dfree((void **)env);
	dfree((void **)args);
	exit(0);
}

void	open_pipe(t_token *cmdline, int fd[2])
{
	if (tok_next_type(cmdline) == Pipe)
		pipe(fd);
}

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
	return (ret_cmd);
}
