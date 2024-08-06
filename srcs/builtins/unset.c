/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:40:25 by bama              #+#    #+#             */
/*   Updated: 2024/08/06 13:59:08 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	not_possible(char *varname)
{
	if (!ft_strcmp(varname, "?")
		|| !varname[0])
		return (1);
	return (0);
}

static char	find_envvar(char *varname, t_data *data)
{
	t_env	*prev;
	t_env	*env;

	prev = NULL;
	env = data->env;
	while (env)
	{
		if (not_possible(varname))
			return (0);
		if (!ft_strcmp(env->name, varname))
		{
			if (prev)
				prev->next = env->next;
			else
				data->env = data->env->next;
			free(env->value);
			free(env->name);
			free(env);
			return (1);
		}
		prev = env;
		env = env->next;
	}
	return (0);
}

int	ft_unset(char **arguments, t_data *data)
{
	size_t	i;

	i = 1;
	while (arguments[i])
		find_envvar(arguments[i++], data);
	data->ret_cmd = SUCCESS;
	return (0);
}
