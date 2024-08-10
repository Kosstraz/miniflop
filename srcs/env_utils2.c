/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 01:27:34 by bama              #+#    #+#             */
/*   Updated: 2024/08/10 01:56:14 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_own_env(t_data *data)
{
	add_new_env(ft_strdup("PATH"), ft_strdup(PATH), &data->env);
	add_new_env(ft_strdup("LSCOLORS"), ft_strdup(LSCOLORS), &data->env);
	add_new_env(ft_strdup("LS_COLORS"), ft_strdup(LS_COLORS), &data->env);
	add_new_env(ft_strdup("TERM"), ft_strdup(DEFAULT_TERM), &data->env);
	add_new_env(ft_strdup("LANG"), ft_strdup("fr_FR.UTF-8"), &data->env);
	add_new_env(ft_strdup("_"), ft_strdup("minishell"), &data->env);
	add_new_env(ft_strdup("SHLVL"), ft_itoa(0), &data->env);
	add_new_env(ft_strdup("OLDPWD"), getcwd(NULL, 0), &data->env);
	add_new_env(ft_strdup("PWD"), getcwd(NULL, 0), &data->env);
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

// Duplique la valeur de la variable d'environnement (ft_strdup)
char	*getenvval(char *envname, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, envname))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

int	setenvval(char *envname, char *newval, t_env **env)
{
	t_env	*tmp;

	if (!env || !newval)
		return (-1);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, envname))
		{
			free(tmp->value);
			tmp->value = newval;
			return (1);
		}
		tmp = tmp->next;
	}
	return (ENVVAR_NOTFOUND);
}

void	increment_shlvl(t_env **env)
{
	char	*shlvl;
	char	*tmp;
	int		i;

	shlvl = getenvval("SHLVL", *env);
	i = ft_atoi(shlvl);
	tmp = shlvl;
	shlvl = ft_itoa(++i);
	free(tmp);
	setenvval("SHLVL", shlvl, env);
}
