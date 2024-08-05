/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:06:34 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/06 00:36:32 by cachetra         ###   ########.fr       */
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

void	initialise_env(t_data *data)
{
	data->env = (t_env *)ft_malloc(sizeof(t_env), data);
	data->env->name = ft_strdup("?");
	data->env->value = ft_strdup("0");
	if (!(data->env->name && data->env->value))
		exit_shell("\e[1;32mft_strdup\e[0m", data, EXIT_FAILURE);
	data->env->next = NULL;
}

void	add_env_to_data(t_data *data, char **env)
{
	int		i;
	t_env	*root;

	i = 0;
	if (!env || !*env)
		return ;
	initialise_env(data);
	root = data->env;
	while (env[i])
	{
		data->env->next = env_create_node(env[i++], data);
		data->env = data->env->next;
	}
	data->env = root;
	increment_shlvl(&data->env);
}

void	free_data(t_data *data)
{
	if (data->tokens)
	{
		free_tokens(&data->tokens);}
	if (data->dir)
		closedir(data->dir);
	data->dir = NULL;
	if (data->fileno[0] != -1)
		close(data->fileno[0]);
	if (data->fileno[1] != -1)
		close(data->fileno[1]);
	if (data->fileno[2] != -1)
		close(data->fileno[2]);
}
