/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:29:59 by bama              #+#    #+#             */
/*   Updated: 2024/11/13 14:48:40 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	write(2, CURLY, ft_strlen(CURLY));
	write(2, LINE_RED, ft_strlen(LINE_RED));
	write(2, cmdline->value, ft_strlen(cmdline->value));
	write(2, R_CURLY, ft_strlen(R_CURLY));
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
	while (i < size && env)
	{
		var = ft_strjoin(ft_strdup(env->name), "=");
		if (env->value)
			var = strljoin(var, ft_strdup(env->value));
		ret[i++] = var;
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}
