/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:41:31 by bama              #+#    #+#             */
/*   Updated: 2024/07/19 18:45:05 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline void	new_prompt(void)
{
	write(1, PROMPT, PROMPT_SIZE);
}

/*static void	read_prompt(void)
{
	char	*gnl;

	gnl = get_next_line(STDIN_FILENO);
	while (gnl)
	{
		take_commandline(gnl);
		new_prompt();
		free(gnl);
		gnl = get_next_line(STDIN_FILENO);
	}
}*/

static void	read_prompt(void)
{
	char	*gnl;

	while (1)
	{
		gnl = readline(PROMPT);
		
		take_commandline(gnl);
	}
}

void	minishell(void)
{
	//new_prompt();
	read_prompt();
}
