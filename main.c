/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:36:30 by bama              #+#    #+#             */
/*   Updated: 2024/08/06 00:47:25 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handle(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
	else if (signum == SIGQUIT)
		write(1, "Quit\n", 5);
}

int	main(int ac, char **av, char **env)
{
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, signal_handle);
	(void)ac;
	(void)av;
	minishell(env);
	return (0);
}
