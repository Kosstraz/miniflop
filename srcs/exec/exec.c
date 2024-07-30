/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:11:58 by bama              #+#    #+#             */
/*   Updated: 2024/07/31 00:22:16 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtin(char builtin_cmd, t_data *data, t_token *cmdline)
{
	char	**strs;
	int		ret_cmd;

	ret_cmd = -ARG_MAX;
	strs = tok_to_strs(cmdline);
	if (builtin_cmd == ECHO_BLT)
		ret_cmd = ft_echo(strs, data);
	else if (builtin_cmd == CD_BLT)
		ret_cmd = ft_cd(strs, data);
	else if (builtin_cmd == UNSET_BLT)
		ret_cmd = ft_unset(strs, data);
	else if (builtin_cmd == EXIT_BLT)
		ret_cmd = ft_exit(strs, data);
	free(strs);
	return (ret_cmd);
}

int	launch_generic(t_token *cmdline, t_data *data)
{
	char	*path_to_f;
	char	**env;
	char	**args;

	path_to_f = search_cmd(cmdline, data);
	closedir(data->dir);
	data->dir = opendir(".");
	if (!path_to_f)
	{
		printf(UNKNOW_CMD_PRINTF, cmdline->value);
		data->ret_cmd = CMD_UNKNOW;
		return (CMD_UNKNOW);
	}
	else
	{
		args = tok_to_strs(cmdline);
		env = convert_env(data->env);
		execve(path_to_f, args, env);
		dfree((void **)env);
		free(args);
		data->ret_cmd = 0;
	}
	return (0);
}

int	exec_cmdline(t_data *data, t_token *cmdline, int is_fork)
{
	int		ret_cmd;
	t_token	*tmp;

	tmp = tok_next_sep(cmdline);
	if (tmp && tmp->type == Pipe)
	{
		close(data->fildes[0]);
		dup2(data->fildes[1], STDOUT_FILENO);
	}
	ret_cmd = -ARG_MAX;
	if (cmdline->type == Command)
		ret_cmd = launch_builtin(is_a_builtin(cmdline->value), data, cmdline);
	if (cmdline->type == Command && ret_cmd == -ARG_MAX)
		ret_cmd = launch_generic(cmdline, data);
	if (tmp && tmp->type == Pipe)
		close(data->fildes[1]);
	if (is_fork)
		exit(data->ret_cmd);
	return (ret_cmd);
}

void	create_fork(t_data *data, t_token *tok, t_token **base)
{
	t_token	*tmp;
	int		pid;
	int		stat;

	tmp = tok_next_sep(tok);
	if (tmp && tmp->type == Pipe)
		pipe(data->fildes);
	pid = fork();
	if (pid == 0)
		exec_cmdline(data, tok, 1);
	else
	{
		if (base && *base)
			(*base) = tmp;
		if (tmp && tmp->type == Pipe)
		{
			close(data->fildes[1]);
			dup2(data->fildes[0], STDIN_FILENO);
			close(data->fildes[0]);
			create_fork(data, tmp->next, base);
		}
		waitpid(pid, &stat, 0);
		data->ret_cmd = stat;
	}
}

void	execution(t_data *data)
{
	t_token	*cmd;
	int		builtins;
	int		fileno[2];

	fileno[0] = dup(STDOUT_FILENO);
	fileno[1] = dup(STDIN_FILENO);
	cmd = data->tokens;
	while (cmd)
		create_fork(data, cmd, &cmd);
	dup2(fileno[0], STDOUT_FILENO);
	dup2(fileno[1], STDIN_FILENO);
}
	// A = open(...)
	// B = open(...) [!=B]
	// tmp
	// tmp = dup(B);
	// dup2(A, B);
	// dup2(tmp, A);


