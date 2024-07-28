/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:41:31 by bama              #+#    #+#             */
/*   Updated: 2024/07/28 12:59:48 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static void	read_prompt(char **env)
{
	t_data	data;
	char	*gnl;

	add_env_to_data(&data, env);
	gnl = get_next_line(STDIN_FILENO);
	while (gnl)
	{
		init_data(&data);
		take_commandline(gnl, &data);
		free_data(&data);
		new_prompt();
		free(gnl);
		gnl = get_next_line(STDIN_FILENO);
	}
	write(1, EXIT_TEXT, EXIT_TEXT_SIZE);
}

void	minishell(char **env)
{
	signal(SIGQUIT, signals_handling);
	signal(SIGINT, signals_handling);
	new_prompt();
	read_prompt(env);
}
