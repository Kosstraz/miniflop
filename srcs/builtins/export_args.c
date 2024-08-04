/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:15:00 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/03 15:16:05 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	export_args(char **args, t_env **head)
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
