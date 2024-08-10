/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:06:34 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/10 01:54:41 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	ft_memset(data->fildes, 0, 2);
	data->npid = 0;
	data->dir = NULL;
	data->tokens = NULL;
	data->exec_next = 1;
	data->_errcode = 0;
	data->blt_val = 0;
	data->fileno[0] = -1;
	data->fileno[1] = -1;
	data->fileno[2] = -1;
}

void	exit_shell(char *mess, t_data *data, int status)
{
	tab_reset(data, 1);
	if (status && mess)
		perror(mess);
	else if (!status && mess)
		write(STDOUT_FILENO, mess, ft_strlen(mess));
	free_shell(data);
	exit(status);
}

void	free_shell(t_data *data)
{
	free_data(data);
	free_env(&data->env);
	kill_term(data);
}

void	free_data(t_data *data)
{
	free_tokens(&data->tokens);
	if (data->dir)
		closedir(data->dir);
	data->dir = NULL;
	free(data->prompt);
	data->prompt = NULL;
	if (data->fileno[0] != -1)
		close(data->fileno[0]);
	if (data->fileno[1] != -1)
		close(data->fileno[1]);
	if (data->fileno[2] != -1)
		close(data->fileno[2]);
}

void	add_env_to_data(t_data *data, char **env)
{
	int		i;
	t_env	*root;

	i = 0;
	initialise_env(data);
	if (!env || !*env)
	{
		create_own_env(data);
		return ;
	}
	root = data->env;
	while (env[i])
	{
		data->env->next = env_create_node(env[i++], data);
		data->env = data->env->next;
	}
	data->env = root;
	increment_shlvl(&data->env);
}
