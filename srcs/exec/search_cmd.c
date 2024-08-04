/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:28:38 by bama              #+#    #+#             */
/*   Updated: 2024/08/03 17:46:18 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	is_a_execbin(char *path_to_f)
{
	struct stat	fstat;

	stat(path_to_f, &fstat);
	if (S_ISREG(fstat.st_mode)
		&& (fstat.st_mode & S_IXUSR || fstat.st_mode & S_IXGRP
			|| fstat.st_mode & S_IXOTH))
		return (1);
	free(path_to_f);
	return (0);
}

static char	*check_in_path(t_token cmdword, t_data *data, char **paths)
{
	size_t			i;
	char			*path_to_f;
	struct dirent	*file;

	i = 0;
	while (paths[i])
	{
		closedir(data->dir);
		data->dir = opendir(paths[i]);
		file = readdir(data->dir);
		while (file)
		{
			if (!ft_strcmp(cmdword.value, file->d_name))
			{
				path_to_f = ft_strjoin(paths[i], "/");
				path_to_f = ft_strsjoin(path_to_f, file->d_name);
				if (is_a_execbin(path_to_f))
					return (path_to_f);
			}
			file = readdir(data->dir);
		}
		i++;
	}
	return (NULL);
}

char	*getcmdpath(t_token *cmdline, t_data *data)
{
	char			*path;
	char			**paths;

	while (cmdline && !is_sep_toktype(*cmdline) && cmdline->type != Command)
		cmdline = cmdline->next;
	if (!cmdline || cmdline->type != Command || is_sep_toktype(*cmdline))
		return (NULL);
	path = getenvval("PATH", data->env);
	paths = ft_split(path, ':');
	free(path);
	if (!paths)
		return (NULL);
	path = check_in_path(*cmdline, data, paths);
	dfree((void **)paths);
	return (path);
}
