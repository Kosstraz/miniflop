/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:50:43 by bama              #+#    #+#             */
/*   Updated: 2024/08/03 17:50:26 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **av, t_data *data)
{
	int	count;
	int	ret;

	count = 0;
	while (av[count + 1])
	{
		count++;
		if (count > 1)
		{
			dfree((void **)av);
			write(1, TOO_MANY_ARGS_ERROR, TOO_MANY_ARGS_ERROR_SIZE);
			data->ret_cmd = ERROR;
			return (ERROR);
		}
	}
	free_shell(data);
	ret = ft_atoi(av[1]);
	dfree((void **)av);
	write(1, EXIT_TEXT, EXIT_TEXT_SIZE);
	data->ret_cmd = SUCCESS;
	if (!count)
		exit(SUCCESS);
	exit(ret);
}
