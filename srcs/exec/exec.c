/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:41:28 by cachetra          #+#    #+#             */
/*   Updated: 2024/11/17 17:00:26 by ymanchon         ###   ########.fr       */
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

char	subshell(t_data *data, t_token **cmd);

void	subshell_exec(t_data *data, t_token *tmp)
{
	save_stdfileno(data->fileno);
	char	*path_to_file;
	char	there_is_redi;
	data->last_is_pipe = FALSE;
	data->firstcmd = TRUE;
	while (tmp)
	{
		if (subshell(data, &tmp))
			continue ;
		path_to_file = NULL;
		there_is_redi = is_there_redirect(tmp);	
		if (there_is_redi && data->exec_next)
			do_redirections(data, tmp, O_RDONLY);
		if (is_there_cmd(tmp) && data->exec_next)
			fetch_command(&path_to_file, &tmp, data);
		if ((data->blt_val || path_to_file || there_is_redi) && data->exec_next)
			launch_cmd(path_to_file, tmp, data);
		if (tok_next_type(tmp) != Pipe)
			waitchildren(data);
		should_next_execute(tmp, data);
		if (tok_next_sep(tmp) && tok_next_sep(tmp)->type == Pipe)
			data->last_is_pipe = TRUE;
		else
			data->last_is_pipe = FALSE;
		if (tmp->next && tmp->next->type == Subshell && !ft_strcmp(tmp->next->value, ")"))
			break ;
			/* NEXT CMD (without Subshell like separator)*/
		while (tmp && !is_justsep_toktype(*tmp))
		tmp = tmp->next;
		if (tmp && is_justsep_toktype(*tmp))
			tmp = tmp->next;
	}
	restore_stdfileno(data->fileno);
	exit(data->ret_cmd);
}

char	subshell(t_data *data, t_token **cmd)
{
	int		pid;
	int		stat;
	t_token	*tmp;

	if ((*cmd)->type == Subshell && !ft_strcmp((*cmd)->value, "("))
	{
		pid = fork();
		stat = 0;
		if (pid == 0)
		{
			tmp = (*cmd)->next;
			subshell_exec(data, tmp);
		}
		else
		{
			waitpid(pid, &stat, 0);
			check_exitedchild(data, &stat);
			data->ret_cmd = stat;
			(*cmd) = tok_next_subshell_out((*cmd));
			(*cmd) = tok_next_cmd((*cmd));
			return (TRUE);
		}
	}
	return (FALSE);
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
		if (subshell(data, &cmd))
			continue ;
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
		if (cmd->next && cmd->next->type == Subshell && !ft_strcmp(cmd->next->value, ")"))
			break ;
		cmd = tok_next_cmd(cmd);
	}
	restore_stdfileno(data->fileno);
}
