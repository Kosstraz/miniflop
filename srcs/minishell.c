/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:41:31 by bama              #+#    #+#             */
/*   Updated: 2024/07/18 10:59:57 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline void	new_prompt(void)
{
	write(1, PROMPT, PROMPT_SIZE);
}

static void	read_prompt(void)
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
}

void	minishell(void)
{
	new_prompt();
	read_prompt();
}
