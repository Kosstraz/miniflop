/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:41:31 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 23:12:15 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_prompt(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	write(1, PROMPT1, PROMPT1_SIZE);
	write(1, cwd, ft_strlen(cwd));
	write(1, PROMPT2, PROMPT2_SIZE);
	write(1, PROMPT3, PROMPT3_SIZE);
	free(cwd);
}

static void	read_prompt(char **env)
{
	t_data	datas;
	char	*gnl;

	add_env_to_datas(&datas, env);
	gnl = get_next_line(STDIN_FILENO);
	while (gnl)
	{
		init_datas(&datas);
		take_commandline(gnl, &datas);
		free_datas(&datas);
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
