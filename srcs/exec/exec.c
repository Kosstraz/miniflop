/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:41:28 by cachetra          #+#    #+#             */
/*   Updated: 2024/11/13 17:51:54 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_cmd(char *path, t_token *cmdline, t_data *data, int forked)
{
	dup2_stdout(data, cmdline, data->fildes);
	dup2_stdin(data, cmdline, data->tmpFildes);
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

	if (tok_next_sep(cmdline) && tok_next_sep(cmdline)->type == Pipe)
	{
		if (pipe(data->fildes) == -1)
			exit_shell("pipe error\n", data, 1);
		data->firstcmd = FALSE;
	}
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
		//setenvval("?", ft_itoa(data->ret_cmd), &data->env);
		if (tok_next_sep(cmdline) && tok_next_sep(cmdline)->type == Pipe && data->fildes[1] != -1)
			close(data->fildes[1]);
	}
	if (data->last_is_pipe)
	{
		if (data->tmpFildes[0] != -1)
			close(data->tmpFildes[0]);
		if (data->tmpFildes[1] != -1)
			close(data->tmpFildes[1]);
	}
	if (tok_next_sep(cmdline) && tok_next_sep(cmdline)->type == Pipe)
	{
		data->tmpFildes[0] = data->fildes[0];
		data->tmpFildes[1] = data->fildes[1];
	}
	return ;
}

//static void	launch_cmd(char *path, t_token *cmdline, t_data *data)
//{
//	int	pid;

//	if (data->last_is_pipe)
//	{
//		if (data->last_fildes0 != -1)
//			close(data->last_fildes0);
//		data->last_fildes0 = data->fildes[0];
//	}
//	if (tok_next_sep(cmdline) && tok_next_sep(cmdline)->type == Pipe)
//	{
//		open_pipe(cmdline, data->fildes);
//		data->firstcmd = FALSE;
//		ft_printf("ez\n");
//	}
//	pid = -2;
//	if (data->blt_val && tok_next_type(cmdline) != Pipe)
//		execute_cmd(path, cmdline, data, 0);
//	else
//		pid = ft_fork(data);
//	if (pid == 0)
//		execute_cmd(path, cmdline, data, 1);
//	else if (data->blt_val == EXIT_BLT && tok_next_type(cmdline) != Pipe
//		&& data->ret_cmd != ERROR)
//	{
//		free(path);
//		exit_shell(EXIT_TEXT, data, data->ret_cmd);
//	}
//	else
//	{
//		if (pid != -2)
//			data->pids[data->npid++] = pid;
//		free(path);
//		setenvval("?", ft_itoa(data->ret_cmd), &data->env);
//		if (tok_next_sep(cmdline) && tok_next_sep(cmdline)->type == Pipe)
//			close(data->fildes[1]);
//	}
//}

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
	data->last_is_pipe = FALSE;
	data->firstcmd = TRUE;
	while (cmd)
	{
		//if (cmd->type == Subshell && ft_strcmp(cmd->value, ")"))
		//	exit(data->ret_cmd);
		//else if (cmd->type == Subshell && ft_strcmp(cmd->value, "("))
		//	exec();
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
		if (tok_next_sep(cmd) && tok_next_sep(cmd)->type == Pipe)
			data->last_is_pipe = TRUE;
		else
			data->last_is_pipe = FALSE;
		cmd = tok_next_cmd(cmd);
	}
	restore_stdfileno(data->fileno);
}
