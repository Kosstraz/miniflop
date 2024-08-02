/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:59:44 by bama              #+#    #+#             */
/*   Updated: 2024/08/03 00:36:32 by bama             ###   ########.fr       */
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
