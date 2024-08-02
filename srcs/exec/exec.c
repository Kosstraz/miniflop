/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:11:58 by bama              #+#    #+#             */
/*   Updated: 2024/08/02 18:46:46 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect(t_data *data, t_token *cmdline, int mode)
{
	t_token	*r;
	char	buffer[ARG_MAX];
	int		fd;

	r = tok_next_redirect(data->tokens);
	if (!r)
		return ;
	if (r->type == RedirectW && mode == O_WRONLY)
	{
		fd = open(r->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (!is_there_cmd(cmdline))
			write(fd, buffer, ARG_MAX);
		dup2(fd, STDOUT_FILENO);
	}
	else if (r->type == RedirectR && r->next->type != HereDoc && mode == O_RDONLY)
	{
		fd = open(r->next->value, O_RDONLY, 0666);
		dup2(fd, data->fildes[0]);
	}
	else if (r->type == RedirectAppend && mode == O_WRONLY)
	{
		fd = open(r->next->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
		restore_stdfileno(data->fileno);
		save_stdfileno(data->fileno);
		if (!is_there_cmd(cmdline))
			write(fd, buffer, ARG_MAX);
		dup2(fd, STDOUT_FILENO);
	}
	// handle HereDoc here
	close(fd);
}

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
		exit(CMD_UNKNOW);
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
	if (is_there_redirect(cmdline))
		redirect(data, cmdline, O_WRONLY);
	ret_cmd = -ARG_MAX;
	if (cmdline->type == Command)
		ret_cmd = launch_builtin(is_a_builtin(cmdline->value), data, cmdline);
	if (cmdline->type == Command && ret_cmd == -ARG_MAX)
		ret_cmd = launch_generic(cmdline, data);
	if (tmp && tmp->type == Pipe)
		close(data->fildes[1]);
	if (is_fork == FORKED)
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
	if (is_there_redirect(tok))
		redirect(data, NULL, O_RDONLY);
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
		if (check_exitedchild(data, &stat) && stat == CMD_UNKNOW)
			fprint_invalidcmd(tok->value);
	}
}

void	execution(t_data *data)
{
	t_token	*cmd;
	t_token	*next_sep;
	int		builtins;
	int		fileno[3];

	save_stdfileno(fileno);
	data->fileno = fileno;
	cmd = data->tokens;
	while (cmd)
	{
		builtins = is_a_builtin(cmd->value);
		next_sep = tok_next_sep(cmd);
		if (builtins != EXIT_BLT
			|| (builtins != EXIT_BLT && next_sep && next_sep->type == Pipe))
			create_fork(data, cmd, &cmd);
		else
		{
			exec_cmdline(data, cmd, 0);
			cmd = tok_next_cmd(cmd);
		}
	}
	restore_stdfileno(fileno);
}
	// inversion de fd
	// A = open(...);
	// B = open(...); [!=B]
	// tmp = dup(B);
	// dup2(A, B);
	// dup2(tmp, A);
	// close(A);
	// close(B);
	// close(tmp);

