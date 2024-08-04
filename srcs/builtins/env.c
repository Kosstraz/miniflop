/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 01:32:54 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/03 20:28:01 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_data *data)
{
	t_env	*tmp;

	if (args[1])
	{
		// dfree((void **)args);
		write(STDERR_FILENO, ENV_ARGS_ERROR, ARGS_ERROR_SIZE);
		data->ret_cmd = ERROR;
		return (ERROR);
	}
	tmp = data->env;
	data->env = data->env->next;
	while (data->env->next)
	{
		data->env = data->env->next;
		if (data->env->next->value)
		{
			write(1, data->env->next->name, ft_strlen(data->env->next->name));
			write(1, "=", 1);
			ft_putendl_fd(data->env->next->value, 1);
		}
	}
	// dfree((void **)args);
	data->env = tmp;
	data->ret_cmd = SUCCESS;
	return (SUCCESS);
}
