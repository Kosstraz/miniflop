/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:39:43 by ymanchon          #+#    #+#             */
/*   Updated: 2024/11/29 15:42:13 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_ctrl_l(t_data *data, char *prompt)
{
	char	*const args[6] = {"clear"};
	char	**env;
	int		pid;

	pid = fork();
	env = convert_env(data->env);
	if (pid == 0)
	{
		execve("/usr/bin/clear", args, env);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	write(1, prompt, ft_strlen(prompt));
	dfree((void **)env);
}
