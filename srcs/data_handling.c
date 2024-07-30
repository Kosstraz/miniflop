/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:06:34 by cachetra          #+#    #+#             */
/*   Updated: 2024/07/30 17:55:19 by bama             ###   ########.fr       */
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
		free(tmp->value);
		free(tmp->name);
		*env = (*env)->next;
		free(tmp);
	}
}

t_env	*env_create_node(const char *var, t_data *data)
{
	t_env	*env;
	size_t	i;

	i = 0;
	env = (t_env *)malloc(sizeof(t_env));
	while (var[i] != '=')
		i++;
	env->name = ft_strndup(var, i);
	if (!env->name)
		free_data(data);
	env->value = ft_strdup(getenv(env->name));
	if (!env->value)
		free_data(data);
	env->next = NULL;
	return (env);
}

void	add_env_to_data(t_data *data, char **env)
{
	t_uint	i;
	t_env	*root;

	i = 0;
	if (!env || !*env)
		return ;
	data->env = env_create_node(env[i++], data);
	root = data->env;
	while (env[i])
	{
		data->env->next = env_create_node(env[i++], data);
		data->env = data->env->next;
	}
	data->env = root;
}

void	free_data(t_data *data)
{
	g_sig = 0;
	free_tokens(&data->tokens);
	if (data->dir)
		closedir(data->dir);
	data->dir = NULL;
}

void	init_data(t_data *data)
{
	ft_memset(data->fildes, 0, 2);
	g_sig = 0;
	data->dir = opendir(".");
	data->tokens = NULL;
	data->_errcode = 0;
}
