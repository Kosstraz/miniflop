/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:08:30 by bama              #+#    #+#             */
/*   Updated: 2024/08/14 16:37:34 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rgb	create_rgb(int r, int g, int b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

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
	prompt = strlljoin(prompt, ft_itoa(data->ret_cmd));
	prompt = strljoin(prompt, "]  ");
	return (prompt);
}

void	new_prompt_heredoc(char **buffer_prompt, t_data *data)
{
	*buffer_prompt = NULL;
	*buffer_prompt = strljoin(*buffer_prompt, HEREDOC_PROMPT);
	*buffer_prompt = create_shading(*buffer_prompt, create_rgb(208, 117, 152),
			create_rgb(-8, 6, 8));
}
