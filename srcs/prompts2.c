/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:08:30 by bama              #+#    #+#             */
/*   Updated: 2024/08/10 02:11:17 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_home_by_tild(char *cwd, t_data *data)
{
	char	*user;
	char	*path;
	char	*newcwd;

	user = getenvval("USER", data->env);
	path = ft_strdup("/home");
	if (user)
		path = strljoin(path, "/");
	path = strlljoin(path, user);
	if (!ft_strncmp(cwd, path, ft_strlen(path)))
		newcwd = ft_strjoin("~", &cwd[ft_strlen(path)]);
	else
		newcwd = ft_strdup(cwd);
	free(path);
	free(cwd);
	return (newcwd);
}

char	*prompt_add_retcmd(char *prompt, t_data *data)
{
	prompt = ft_strdup("[");
	prompt = strlljoin(prompt, getenvval("?", data->env));
	prompt = strljoin(prompt, "]  ");
	return (prompt);
}
