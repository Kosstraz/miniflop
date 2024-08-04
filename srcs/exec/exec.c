/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:52:08 by bama              #+#    #+#             */
/*   Updated: 2024/08/03 02:08:06 by cachetra         ###   ########.fr       */
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
	dfree((void **)args);
	dfree((void **)env);
	free(path);
	exit(0);
}

void	execute_cmd(char *path, t_token *cmdline, t_data *data, int forked)
{
	if (tok_next_type(cmdline) == Pipe)
		dup2_stdout(data->fildes);
	if (!path)
		data->ret_cmd = exec_builtins(data->blt_val, data, cmdline);
	else
		custom_execve(path, cmdline, data);
	if (forked)
		exit(data->ret_cmd);
}

void	launch_cmd(char *path, t_token *cmdline, t_data *data)
{
	int	pid;
	int	stat;

	if (tok_next_type(cmdline) == Pipe)
		pipe(data->fildes);
	pid = 1;
	if (data->blt_val && tok_next_type(cmdline) != Pipe)
		execute_cmd(path, cmdline, data, 0);
	else
		pid = fork();
	if (pid == 0)
		execute_cmd(path, cmdline, data, 1);
	else if (data->blt_val == EXIT_BLT && tok_next_type(cmdline) != Pipe)
	{
		free(path);
		free_shell(data);
		write(1, EXIT_TEXT, EXIT_TEXT_SIZE);
		exit(0);
	}
	else
	{
		waitpid(pid, &stat, 0);
		check_exitedchild(data, &stat);
		data->ret_cmd = stat;
		if (tok_next_type(cmdline) == Pipe)
			dup2_stdin(data->fildes);
	}
}

void	exec(t_data *data)
{
	t_token	*cmd;
	char	*path_to_file;

	cmd = data->tokens;
	save_stdfileno(data->fileno);
	while (cmd)
	{
		if (is_there_cmd(cmd))
		{
			path_to_file = NULL;
			data->blt_val = is_a_builtin(cmd);
			if (!data->blt_val)
			{
				path_to_file = getcmdpath(cmd, data);
				if (!path_to_file)
					fprint_invalidcmd(cmd);
			}
			if (data->blt_val || path_to_file)
				launch_cmd(path_to_file, cmd, data);
		}
		free(path_to_file);
		cmd = tok_next_cmd(cmd);
	}
	restore_stdfileno(data->fileno);
}
