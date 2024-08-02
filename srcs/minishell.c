/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:41:31 by bama              #+#    #+#             */
/*   Updated: 2024/08/01 14:44:44 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_prompt(char **env)
{
	t_data	data;
	char	*prompt;
	char	*gnl;

	term_init(&data);
	add_env_to_data(&data, env);
	new_prompt(&prompt);
	gnl = ft_readline(prompt, &data);
	free(prompt);
	while (gnl)
	{
		init_data(&data);
		take_commandline(gnl, &data);
		free_data(&data);
		free(gnl);
		new_prompt(&prompt);
		gnl = ft_readline(prompt, &data);
		free(prompt);
	}
	free_env(&data.env);
	write(1, EXIT_TEXT, EXIT_TEXT_SIZE);
}

void	minishell(char **env)
{
	signal(SIGQUIT, signals_handling);
	signal(SIGINT, signals_handling);
	read_prompt(env);
}
