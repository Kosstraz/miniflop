/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:41:31 by bama              #+#    #+#             */
/*   Updated: 2024/08/03 01:30:13 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char **env)
{
	t_data	data;
	char	*prompt;
	char	*rl;

	term_init(&data);
	add_env_to_data(&data, env);
	while (1)
	{
		if (data.term.state == CANON)
			term_set_raw(&data);
		init_data(&data);
		new_prompt(&prompt);
		rl = ft_readline(prompt, &data);
		term_reset(&data);
		take_commandline(rl, &data);
		free(rl);
		free(prompt);
		free_data(&data);
	}
	free_env(&data.env);
	kill_term(&data);
	write(1, EXIT_TEXT, EXIT_TEXT_SIZE);
}
