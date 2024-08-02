/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:36:30 by bama              #+#    #+#             */
/*   Updated: 2024/08/03 00:17:29 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// to do
// signal ctrl-\ && ctrl-c en mode non-interactif	- OK
// g_sig modification et lecture
// envoi de signaux aux processus enfant
// export
// export $arg										- OK
// export with $
// $?
// copier-coller

// ^\Quit
// ^C

#include "minishell.h"

char	g_sig = 0;

void	signal_handle(int signum)
{
	g_sig = (char)signum;
	if (signum == SIGINT)
		write(0, "\n", 1);
	else if (signum == SIGQUIT)
		write(0, "Quit\n", 5);
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
