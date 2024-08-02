/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:59:44 by bama              #+#    #+#             */
/*   Updated: 2024/08/01 14:15:09 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_prompt(char **buffer_prompt)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	*buffer_prompt = ft_strdup(PROMPT1);
	*buffer_prompt = ft_strsjoin(*buffer_prompt, cwd);
	*buffer_prompt = ft_strsjoin(*buffer_prompt, PROMPT2);
	*buffer_prompt = ft_strsjoin(*buffer_prompt, PROMPT3);
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
