/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 01:45:55 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/06 13:46:13 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, t_data *data)
{
	char	*buf;

	buf = NULL;
	if (args[1])
	{
		write(STDERR_FILENO, PWD_ARGS_ERROR, ARGS_ERROR_SIZE);
		data->ret_cmd = ERROR;
		return (ERROR);
	}
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		exit_shell("\e[31mgetcwd", data, EXIT_FAILURE);
	}
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	data->ret_cmd = SUCCESS;
	return (SUCCESS);
}
