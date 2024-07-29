/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:40:25 by bama              #+#    #+#             */
/*   Updated: 2024/07/23 19:06:08 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data, char *varname)
{
	t_env	*env;
	t_env	*prev;

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
			free(env->name);
			free(env);
			return (0);
		}
		prev = env;
		env = env->next;
	}
	return (0);
}
