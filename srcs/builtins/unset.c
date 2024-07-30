/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:40:25 by bama              #+#    #+#             */
/*   Updated: 2024/07/30 14:15:48 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_envvar(char *varname, t_data *data)
{
	t_env	*prev;
	t_env	*env;

	prev = NULL;
	env = data->env;
	while (env)
	{
		if (!ft_strcmp(env->name, varname))
		{
			if (prev)
				prev->next = env->next;
			else
				data->env = data->env->next;
			free(env->value);
			free(env->name);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

int	ft_unset(char **arguments, t_data *data)
{
	size_t	i;

	i = 1;
	while (arguments[i])
		find_envvar(arguments[i++], data);
	print_env(data->env);
	data->ret_cmd = SUCCESS;
	return (0);
}
