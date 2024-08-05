/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:28:31 by bama              #+#    #+#             */
/*   Updated: 2024/08/06 00:58:16 by cachetra         ###   ########.fr       */
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

int	ft_fork(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_shell("\e[31mfork\e[0m", data, EXIT_FAILURE);
	return (pid);
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
	else if (blt_val == ENV_BLT)
		ret_cmd = ft_env(strs, data);
	else if (blt_val == EXPORT_BLT)
		ret_cmd = ft_pwd(strs, data);
	else if (blt_val == LS_BLT)
		ret_cmd = ft_ls(strs, data);
	return (ret_cmd);
}
