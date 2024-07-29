/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:59:44 by bama              #+#    #+#             */
/*   Updated: 2024/07/28 13:04:10 by bama             ###   ########.fr       */
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

void	new_missing_prompt(char _errcode)
{
	if (_errcode == DQUOTE_MISSING)
		write(1, DQUOTE_PROMPT, DQUOTE_PROMPT_SIZE);
	else if (_errcode == SQUOTE_MISSING)
		write(1, SQUOTE_PROMPT, SQUOTE_PROMPT_SIZE);
	else
	{
		if (_errcode == PIPE_MISSING)
			write(1, PIPE_PROMPT, PIPE_PROMPT_SIZE);
		else if (_errcode == AND_MISSING)
			write(1, AND_PROMPT, AND_PROMPT_SIZE);
		else
			if (_errcode == OR_MISSING)
				write(1, OR_PROMPT, OR_PROMPT_SIZE);
	}
}
