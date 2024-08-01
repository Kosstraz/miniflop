/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:29:59 by bama              #+#    #+#             */
/*   Updated: 2024/08/01 12:46:09 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_a_builtin(const char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO_BLT);
	else if (!ft_strcmp(cmd, "cd"))
		return (CD_BLT);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET_BLT);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT_BLT);
	return (0);
}

char	check_exitedchild(int *status)
{
	if (WIFEXITED((*status)))
	{
		(*status) = WEXITSTATUS((*status));
		return (1);
	}
	return (0);
}

void	fprint_invalidcmd(const char *cmdword)
{
	write(2, UNKNOW_CMD_PRINTF1, UNKNOW_CMD_PRINTF1_SIZE);
	write(2, cmdword, ft_strlen(cmdword));
	write(2, UNKNOW_CMD_PRINTF2, UNKNOW_CMD_PRINTF2_SIZE);
}

static size_t	t_env_size(t_env *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**convert_env(t_env *env)
{
	char	**ret;
	char	*var;
	size_t	i;
	size_t	size;

	size = t_env_size(env);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		var = ft_strjoin(env->name, "=");
		var = ft_strsjoin(var, env->value);
		ret[i++] = var;
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}
