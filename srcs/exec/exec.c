/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:11:58 by bama              #+#    #+#             */
/*   Updated: 2024/07/30 15:02:50 by bama             ###   ########.fr       */
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
	char	**args;

	path_to_f = search_cmd(cmdline, data);
	closedir(data->dir);
	data->dir = opendir(".");
	if (!path_to_f)
	{
		write(1, "Commande inconnue :/\n", 21);
		data->ret_cmd = CMD_UNKNOW;
		return (CMD_UNKNOW);
	}
	else
	{
		args = tok_to_strs(cmdline);
		execve(path_to_f, args, NULL);
		free(args);
		data->ret_cmd = 0;
	}
	return (0);
}

int	exec_cmdline(t_data *data, t_token *cmdline)
{
	int		ret_cmd;

	ret_cmd = -ARG_MAX;
	if (cmdline->type == Command)
		ret_cmd = launch_builtin(is_a_builtin(cmdline->value), data, cmdline);
	if (cmdline->type == Command && ret_cmd == -ARG_MAX)
		ret_cmd = launch_generic(cmdline, data);
	return (ret_cmd);
}

void	create_fork(t_data *data, t_token *tok)
{
	t_token	*tmp;
	int		pid;
	int		stat;

	pid = fork();
	if (pid == 0)
		exec_cmdline(data, tok);
	else
	{
		tmp = tok_next_cmd(data->tokens);
		if (tmp && tmp->type == Pipe)
			create_fork(data, tmp->next);
		waitpid(pid, &stat, 0);
	}
}

void	execution(t_data *data)
{
	t_token	*tmp;
	t_token	*root;

	root = data->tokens;
	while (root)
	{
		tmp = tok_next_cmd(root);
		if (tmp && tmp->type == Pipe)
		{
			create_fork(data, root);
			tmp = root;
			while (tmp && (tmp->type == And || tmp->type == Or))
				tmp = tmp->next;
			if (tmp && is_sep_toktype(*tmp))
				tmp = tmp->next;
			root = tmp;
		}
		else
			exec_cmdline(data, root);
		root = root->next;
	}
}


