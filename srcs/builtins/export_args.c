/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:15:00 by cachetra          #+#    #+#             */
/*   Updated: 2024/11/17 16:43:14 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_overwrite(char *arg, t_env **node, t_env *first)
{
	(void)first;
	if (arg)
	{
		free((*node)->value);
		(*node)->value = ft_strdup(arg);
		if (!(*node)->value)
			return (0);
		//(*node) = first;
	}
	else
	{
		free((*node)->value);
		(*node)->value = NULL;
		//(*node) = first;
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
	size_t	i;
	size_t	len;
	t_env	*tmp;

	i = 1;
	while (args[i])
	{
		tmp = (*head);
		len = 0;
		while (args[i][len] && args[i][len] != '=')
			len++;
		if (!ft_strncmp(args[i], "?", len))
		{
			i++;
			ft_printf("%s%s", EXPORT_IDENTIFIER1, EXPORT_IDENTIFIER2);
			continue ;
		}
		while ((*head)->next)
		{
			if (!ft_strncmp((*head)->name, args[i], len))
				break ;
			(*head) = (*head)->next;
		}
		if (!ft_strncmp((*head)->name, args[i], len))
		{
			if (ft_strlen(args[i]) > len)
				env_overwrite(&args[i][++len], head, tmp);
			else
				env_overwrite(NULL, head, tmp);
		}
		else
			(*head)->next = env_export_node(args[i]);
		(*head) = tmp;
		i++;
	}
	return (1);
}
