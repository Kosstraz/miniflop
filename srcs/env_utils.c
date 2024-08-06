/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:12:09 by bama              #+#    #+#             */
/*   Updated: 2024/08/06 23:28:36 by bama             ###   ########.fr       */
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
