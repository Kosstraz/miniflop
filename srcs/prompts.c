/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:59:44 by bama              #+#    #+#             */
/*   Updated: 2024/08/06 23:15:13 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_at_to_env(char *value, t_data *data)
{
	if (!env_exist(CWD_AT_NAME, data))
		add_new_env(ft_strdup(CWD_AT_NAME), value, &data->env);
	else
		setenvval(CWD_AT_NAME, value, &data->env);
}

void	new_prompt(char **buffer_prompt, t_data *data)
{
	char	*cwd;
	char	*tmp;
	int		size;

	cwd = getcwd(NULL, 0);
	size = ft_strlen(cwd);
	if (size > CWD_MAX_LEN)
	{
		while (cwd[size - CWD_MAX_LEN] && cwd[size - CWD_MAX_LEN] != '/')
			size++;
		add_at_to_env(ft_strdup_at(cwd, 0, size - CWD_MAX_LEN), data);
		cwd = ft_strdup_atfree(cwd, size - CWD_MAX_LEN, size);
		tmp = cwd;
		cwd = ft_strjoin("@", cwd);
		free(tmp);
	}
	else
		if (env_exist(CWD_AT_NAME, data))
			env_remove(CWD_AT_NAME, &data->env);
	*buffer_prompt = ft_strdup(PROMPT1);
	*buffer_prompt = ft_strsjoin(*buffer_prompt, cwd);
	*buffer_prompt = ft_strsjoin(*buffer_prompt, PROMPT2);
	*buffer_prompt = ft_strsjoin(*buffer_prompt, PROMPT3);
	data->prompt = (*buffer_prompt);
	free(cwd);
}
