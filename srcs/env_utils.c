/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:12:09 by bama              #+#    #+#             */
/*   Updated: 2024/08/10 01:27:23 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_remove(char *name, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	prev = NULL;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (!prev)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

// 1 exist
// 0 doesnt exist
char	env_exist(char *name, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (tmp->name && !ft_strcmp(tmp->name, name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	add_new_env(char *name, char *value, t_env	**env)
{
	t_env	*new;
	t_env	*tmp;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = name;
	new->value = value;
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

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
	env = (t_env *)ft_malloc(sizeof(t_env), data);
	while (var[i] != '=')
		i++;
	env->name = ft_strndup(var, i);
	if (!env->name)
		free_data(data);
	if (!ft_strcmp(var, "USER"))
		env->value = getenv(env->name);
	else
		env->value = ft_strdup(getenv(env->name));
	if (!env->value)
		exit_shell(NULL, data, 1);
	env->next = NULL;
	return (env);
}
