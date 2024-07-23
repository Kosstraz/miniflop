/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:06:34 by cachetra          #+#    #+#             */
/*   Updated: 2024/07/23 17:59:12 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (*env)
	{
		tmp = *env;
		// free(tmp->name);
		// free(tmp->value);
		*env = (*env)->next;
		free(tmp);
	}
}

void	env_addback(t_env **env, t_env *new)
{
	t_env	*tmp;
	tmp = NULL;
	if (*env)
	{
		tmp = *env;
		while ((*env)->next)
			*env = (*env)->next;
		(*env)->next = new;
		*env = tmp;
	}
	else
		*env = new;
}

void	add_env_to_data(t_data *data, char **env)
{
	t_uint	i;
	t_uint	j;
	t_env	*tmp;

	i = 0;
	while (env[i])
	{
		j = 0;
		tmp = (t_env *)malloc(sizeof(t_env));
		while (env[i][j] != '=')
			j++;
		tmp->name = ft_strndup(env[i++], j);
		if (!tmp->name)
			free_data(data);
		tmp->value = getenv(tmp->name);
		if (!tmp->value)
			free_data(data);
		tmp->next = NULL;
		env_addback(&data->env, tmp);
	}
}

void	free_data(t_data *data)
{
	free_tokens(&data->tokens);
	free_env(&data->env);
}

// void	init_data(t_data *data)
// {
// 	data->tokens = NULL;
// 	data->command_ret = 0;
// 	data->_errcode = 0;
// }
