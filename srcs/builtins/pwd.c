/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 01:45:55 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/03 20:28:04 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, t_data *data)
{
	char	*buf;

	buf = NULL;
	if (args[1])
	{
		dfree((void **)args);
		write(STDERR_FILENO, PWD_ARGS_ERROR, ARGS_ERROR_SIZE);
		data->ret_cmd = ERROR;
		return (ERROR);
	}
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		dfree((void **)args);
		exit_shell("\e[31mgetcwd", data, EXIT_FAILURE);
	}
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	// dfree((void **)args);
	data->ret_cmd = SUCCESS;
	return (SUCCESS);
}
