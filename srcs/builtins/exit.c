/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:50:43 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 23:11:38 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **av, t_data *datas)
{
	int	count;

	count = 0;
	while (av[count + 1])
	{
		count++;
		if (count > 1)
		{
			write(1, TOO_MANY_ARGS_ERROR, TOO_MANY_ARGS_ERROR_SIZE);
			free_datas(datas);
			exit(1);
		}
	}
	free_datas(datas);
	if (!count)
		exit(0);
	exit(ft_atoi(av[1]));
}
