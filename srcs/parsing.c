/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:08:41 by bama              #+#    #+#             */
/*   Updated: 2024/07/18 00:48:14 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	take_commandline(const char *line)
{
	t_token	
	parse_line(line);
}

void	read_prompt(void)
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
