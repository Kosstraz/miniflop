/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:06:34 by cachetra          #+#    #+#             */
/*   Updated: 2024/07/22 23:11:45 by cachetra         ###   ########.fr       */
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
		tmp = (*env)->next;
		free((*env)->name);
		free((*env)->value);
		*env = tmp;
		free(tmp);
	}
}

void	add_env_to_data(t_data *data, char **env)
{
	t_uint	i;
	t_uint	j;
	t_env	*tmp;

	i = 0;
	tmp = data->env;
	while (env[i])
	{
		j = 0;
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			free_data(data);
		while (env[i][j] && env[i][j] != '=')
			j++;
		tmp->name = ft_strndup(env[i], j);
		if (!tmp->name)
			free_data(data);
		tmp->value = getenv(tmp->name);
		if (!tmp->value)
			free_data(data);
		tmp = tmp->next;
		i++;
	}
}

void	free_data(t_data *data)
{
	free_tokens(&data->tokens);
	free_env(data->env);
}

// void	init_data(t_data *data)
// {
// 	data->tokens = NULL;
// 	data->command_ret = 0;
// 	data->_errcode = 0;
// }
