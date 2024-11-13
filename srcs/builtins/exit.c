/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:50:43 by bama              #+#    #+#             */
/*   Updated: 2024/11/13 14:39:13 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_quit(char onlydigits, char **av, t_data *data)
{
	int	ret;

	free_shell(data);
	if (!av[1])
	{
		dfree((void **)av);
		write(1, EXIT_TEXT, EXIT_TEXT_SIZE);
		exit(SUCCESS);
	}
	ret = ft_atoi(av[1]);
	dfree((void **)av);
	write(1, EXIT_TEXT, EXIT_TEXT_SIZE);
	data->ret_cmd = SUCCESS;
	if (onlydigits)
		exit(ret);
	else
	{
		write(2, EXIT_ALNUM, EXIT_ALNUM_SIZE);
		exit(ERROR + 1);
	}
	exit(ret);
}

int	ft_exit(char **av, t_data *data)
{
	if (av[1])
	{
		if (!strisdigits(av[1]))
			exit(ft_exit_quit(0, av, data));
		else if (av[2])
		{
			write(2, TOO_MANY_ARGS_ERROR, TOO_MANY_ARGS_ERROR_SIZE);
			data->ret_cmd = ERROR;
			return (ERROR);
		}
	}
	exit(ft_exit_quit(1, av, data));
}
