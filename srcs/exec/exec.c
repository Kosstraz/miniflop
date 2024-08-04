/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:52:08 by bama              #+#    #+#             */
/*   Updated: 2024/08/04 22:06:25 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(char *path, t_token *cmdline, t_data *data, int forked)
{
	dup2_stdout(cmdline, data->fildes);
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

	open_pipe(cmdline, data->fildes);
	pid = -1;
	if (data->blt_val && tok_next_type(cmdline) != Pipe)
		execute_cmd(path, cmdline, data, 0);
	else
		pid = fork();
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
		if (pid != -1)
			data->pids[data->npid++] = pid;
		free(path);
		setenvval("?", ft_itoa(data->ret_cmd), &data->env);
		dup2_stdin(cmdline, data->fildes);
	}
}

void	fetch_command(char **ptf, t_token *cmdline, t_data *data)
{
	data->blt_val = is_a_builtin(cmdline);
	if (!data->blt_val)
	{
		*ptf = getcmdpath(cmdline, data);
		if (!*ptf)
		{
			fprint_invalidcmd(cmdline);
			setenvval("?", ft_itoa(CMD_UNKNOW), &data->env);
		}
		else
			setenvval("_", ft_strdup(*ptf), &data->env);
	}
}

void	do_redirections(t_token *cmdline, int mode)
{
	int		fd;
	t_token	*r;

	r = tok_next_redirect(cmdline);
	if (mode == O_RDONLY && r->type == RedirectR)
	{
		fd = open(r->next->value, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		return ;
	}
	else if (mode == O_WRONLY)
	{
		if (r->type == RedirectW)
			fd = open(r->next->value, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (r->type == RedirectAppend)
			fd = open(r->next->value, O_WRONLY | O_APPEND | O_CREAT, 0666);
		else
			return ;
		dup2(fd, STDOUT_FILENO);
		close(fd);
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
		path_to_file = NULL;
		if (is_there_redirect(cmd))
			do_redirections(cmd, O_RDONLY);
		if (is_there_cmd(cmd))
			fetch_command(&path_to_file, cmd, data);
		if (data->blt_val || path_to_file)
			launch_cmd(path_to_file, cmd, data);
		if (tok_next_type(cmd) != Pipe)
			waitchildren(data);
		cmd = tok_next_cmd(cmd);
	}
	restore_stdfileno(data->fileno);
}
