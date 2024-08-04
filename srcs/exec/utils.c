/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:29:59 by bama              #+#    #+#             */
/*   Updated: 2024/08/04 15:09:32 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_a_builtin(t_token *cmdline)
{
	char	*cmd;

	while (cmdline && cmdline->type != Command)
		cmdline = cmdline->next;
	cmd = (char *)cmdline->value;
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO_BLT);
	else if (!ft_strcmp(cmd, "cd"))
		return (CD_BLT);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET_BLT);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT_BLT);
	else if (!ft_strcmp(cmd, "export"))
		return (EXPORT_BLT);
	else if (!ft_strcmp(cmd, "env"))
		return (ENV_BLT);
	else if (!ft_strcmp(cmd, "pwd"))
		return (PWD_BLT);
	return (0);
}

char	check_exitedchild(t_data *data, int *status)
{
	if (WIFEXITED((*status)))
	{
		(*status) = WEXITSTATUS((*status));
		data->ret_cmd = (*status);
		return (1);
	}
	return (0);
}

void	fprint_invalidcmd(t_token	*cmdline)
{
	while (cmdline && cmdline->type != Command)
		cmdline = cmdline->next;
	write(2, UNKNOW_CMD_PRINTF1, UNKNOW_CMD_PRINTF1_SIZE);
	write(2, cmdline->value, ft_strlen(cmdline->value));
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

	if (!env)
		return (NULL);
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
