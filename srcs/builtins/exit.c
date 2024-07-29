/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:50:43 by bama              #+#    #+#             */
/*   Updated: 2024/07/22 22:47:44 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **av, t_data *data)
{
	int	count;

	count = 0;
	while (av[count + 1])
	{
		count++;
		if (count > 1)
		{
			write(1, TOO_MANY_ARGS_ERROR, TOO_MANY_ARGS_ERROR_SIZE);
			free_data(data);
			exit(1);
		}
	}
	free_data(data);
	if (!count)
		exit(0);
	exit(ft_atoi(av[1]));
}
