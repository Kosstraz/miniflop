/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:28:31 by bama              #+#    #+#             */
/*   Updated: 2024/08/09 19:54:58 by bama             ###   ########.fr       */
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
	free(path);
	dfree((void **)env);
	dfree((void **)args);
	exit(0);
}

void	open_pipe(t_token *cmdline, int fd[2])
{
	if (tok_next_type(cmdline) == Pipe)
		pipe(fd);
}

int	ft_fork(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_shell("\e[31mfork\e[0m", data, EXIT_FAILURE);
	return (pid);
}
