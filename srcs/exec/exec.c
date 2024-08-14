/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:41:28 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/14 16:39:24 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_cmd(char *path, t_token *cmdline, t_data *data, int forked)
{
	dup2_stdout(data, cmdline, data->fildes);
	if (!path)
		data->ret_cmd = exec_builtins(data->blt_val, data, cmdline);
	else
		custom_execve(path, cmdline, data);
	if (forked)
		exit(data->ret_cmd);
}

static void	launch_cmd(char *path, t_token *cmdline, t_data *data)
{
	int	pid;

	open_pipe(cmdline, data->fildes);
	pid = -2;
	if (data->blt_val && tok_next_type(cmdline) != Pipe)
		execute_cmd(path, cmdline, data, 0);
	else
		pid = ft_fork(data);
	if (pid == 0)
		execute_cmd(path, cmdline, data, 1);
	else if (data->blt_val == EXIT_BLT && tok_next_type(cmdline) != Pipe
		&& data->ret_cmd != ERROR)
	{
		free(path);
		exit_shell(EXIT_TEXT, data, data->ret_cmd);
	}
	else
	{
		if (pid != -2)
			data->pids[data->npid++] = pid;
		free(path);
		setenvval("?", ft_itoa(data->ret_cmd), &data->env);
		dup2_stdin(data, cmdline, data->fildes);
	}
}

static void	fetch_command(char **ptf, t_token **cmdline, t_data *data)
{
	*ptf = catch_execbin(*cmdline);
	if (!ptf || (ptf && !*ptf))
		data->blt_val = is_a_builtin(*cmdline);
	if (!data->blt_val)
	{
		if (!ptf || (ptf && !*ptf))
			*ptf = getcmdpath(cmdline, data);
		if (!*ptf)
		{
			fprint_invalidcmd(*cmdline);
			data->ret_cmd = CMD_UNKNOW;
			setenvval("?", ft_itoa(CMD_UNKNOW), &data->env);
		}
		else
			setenvval("_", ft_strdup(*ptf), &data->env);
	}
}

static void	should_next_execute(t_token *cmd, t_data *data)
{
	t_e_type	next;
	t_token		*check;

	check = tok_next_sep(cmd);
	if (!check)
		return ;
	next = check->type;
	if (next != And && next != Or)
		return ;
	data->exec_next = ((next == Or && data->ret_cmd)
			|| (next == And && !data->ret_cmd));
}

void	exec(t_data *data)
{
	t_token	*cmd;
	char	*path_to_file;
	char	there_is_redi;

	cmd = data->tokens;
	save_stdfileno(data->fileno);
	while (cmd)
	{
		path_to_file = NULL;
		there_is_redi = is_there_redirect(cmd);
		if (there_is_redi && data->exec_next)
			do_redirections(data, cmd, O_RDONLY);
		if (is_there_cmd(cmd) && data->exec_next)
			fetch_command(&path_to_file, &cmd, data);
		if ((data->blt_val || path_to_file || there_is_redi) && data->exec_next)
			launch_cmd(path_to_file, cmd, data);
		if (tok_next_type(cmd) != Pipe)
			waitchildren(data);
		should_next_execute(cmd, data);
		cmd = tok_next_cmd(cmd);
	}
	restore_stdfileno(data->fileno);
}
