/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handling2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:17:47 by bama              #+#    #+#             */
/*   Updated: 2024/08/09 00:51:08 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_shell(t_data *data)
{
	kill_term(data);
	free_env(&data->env);
	free_data(data);
	if (data->historyfd != -1)
		close(data->historyfd);
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

void	exit_shell(char *mess, t_data *data, int status)
{
	tab_reset(data, 1);
	if (status && mess)
		perror(mess);
	else if (!status && mess)
		write(STDOUT_FILENO, mess, ft_strlen(mess));
	free_shell(data);
	exit(status);
}
