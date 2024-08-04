/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:42:00 by bama              #+#    #+#             */
/*   Updated: 2024/08/03 22:03:21 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_stdfileno(int fileno_[3])
{
	fileno_[0] = dup(STDIN_FILENO);
	fileno_[1] = dup(STDOUT_FILENO);
	fileno_[2] = dup(STDERR_FILENO);
}

void	restore_stdfileno(int fileno_[3])
{
	dup2(fileno_[0], STDIN_FILENO);
	dup2(fileno_[1], STDOUT_FILENO);
	dup2(fileno_[2], STDERR_FILENO);
}

void	dup2_stdin(t_token *cmdline, int fd[2])
{
	if (tok_next_type(cmdline) == Pipe)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (is_there_redirect(cmdline))
			do_redirections(cmdline, O_RDONLY);
	}
}

void	dup2_stdout(t_token *cmdline, int fd[2])
{
	if (is_there_redirect(cmdline))
		do_redirections(cmdline, O_WRONLY);
	if (tok_next_type(cmdline) == Pipe)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

void	waitchildren(t_data *data)
{
	int	stat;

	while (data->npid)
	{
		stat = 0;
		waitpid(data->pids[--data->npid], &stat, 0);
		check_exitedchild(data, &stat);
		data->ret_cmd = stat;
	}
}