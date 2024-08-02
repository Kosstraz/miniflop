/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:13:33 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/02 23:31:02 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*env_sort(t_env *env)
{
	int		s_diff;
	t_env	*tmp;

	tmp = env;
	while (env)
	{

	}
}

static t_env	*ez_sort(t_env *env)
{
	t_env	*head;
	t_env	*node;
	t_env	*tmp;

	head = env;
	while (env)
	{
		node = env->next;
		while (node)
		{
			if (ft_strcmp(env->name, node->name) < 0)
				continue ;
			tmp = node;
		}
		env = env->next;
	}
	return (head);
}

static int	env_overwrite(char *arg, t_env **node, t_env *first)
{
	if (arg)
	{
		free((*node)->value);
		(*node)->value = ft_strdup(arg);
		if (!(*node)->value)
			return (0);
		(*node) = first;
	}
	return (1);
}

static t_env	*env_export_node(char *arg)
{
	t_env	*env;
	size_t	i;

	i = 0;
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	while (arg[i] && arg[i] != '=')
		i++;
	env->name = ft_strndup(arg, i);
	if (!env->name)
		return (NULL);
	if (arg[i] == '=' && arg[i + 1])
	{
		env->value = ft_strdup(&arg[++i]);
		if (!env->value)
			return (NULL);
	}
	else
		env->value = NULL;
	env->next = NULL;
	return (env);
}

static int	export_args(char **args, t_env **head)
{
	int		i;
	int		len;
	t_env	*tmp;

	i = 0;
	while (args[++i])
	{
		len = 0;
		tmp = (*head);
		while (args[i][len] && args[i][len] != '=')
			len++;
		while ((*head)->next)
		{
			if (!ft_strncmp((*head)->name, args[i], len))
				return (env_overwrite(&args[i][++len], head, tmp));
			(*head) = (*head)->next;
		}
		(*head)->next = env_export_node(args[i]);
		if (!(*head)->next)
			return (0);
		(*head) = tmp;
	}
	return (1);
}

int	ft_export(char **args, t_data *data)
{
	t_env	*tmp;

	if (!args[1])
	{
		tmp = data->env;

	}
	else
		if (!export_args(args, &data->env))
			exit_shell("\e[1;31`mmalloc\e[0m", data, EXIT_FAILURE);
	print_env(data->env);
	data->ret_cmd = 0;
	return (0);
}
