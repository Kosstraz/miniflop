/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:42:00 by bama              #+#    #+#             */
/*   Updated: 2024/08/02 21:53:57 by bama             ###   ########.fr       */
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

void	dup2_stdin(int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	dup2_stdout(int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
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
	free(strs);
	return (ret_cmd);
}
