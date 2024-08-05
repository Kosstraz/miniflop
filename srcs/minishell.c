/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:41:31 by bama              #+#    #+#             */
/*   Updated: 2024/08/05 19:53:50 by bama             ###   ########.fr       */
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
	data.ret_cmd = 0;
	while (1)
	{
		if (data.term.state == CANON)
			term_set_raw(&data);
		init_data(&data);
		new_prompt(&prompt);
		rl = ft_readline(prompt, &data);
		term_reset(&data);
		free(prompt);
		take_commandline(rl, &data);
		free(rl);
		free_data(&data);
	}
	free_env(&data.env);
	kill_term(&data);
	write(1, EXIT_TEXT, EXIT_TEXT_SIZE);
}
