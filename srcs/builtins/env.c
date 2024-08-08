/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 01:32:54 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/09 01:11:10 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_data *data)
{
	t_env	*tmp;

	if (args[1])
	{
		write(STDERR_FILENO, ENV_ARGS_ERROR, ARGS_ERROR_SIZE);
		data->ret_cmd = ERROR;
		return (ERROR);
	}
	tmp = data->env;
	while (data->env)
	{
		if (data->env->value && ft_strcmp("?", data->env->name))
		{
			write(1, data->env->name, ft_strlen(data->env->name));
			write(1, "=", 1);
			ft_putendl_fd(data->env->value, 1);
		}
		data->env = data->env->next;
	}
	data->env = tmp;
	data->ret_cmd = SUCCESS;
	return (SUCCESS);
}
