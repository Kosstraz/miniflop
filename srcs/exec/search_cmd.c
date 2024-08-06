/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:28:38 by bama              #+#    #+#             */
/*   Updated: 2024/08/07 00:00:17 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_an_execbin(char *path_to_f)
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

static char	*check_in_path(t_token **cmdword, t_data *data, char **paths)
{
	size_t			i;
	char			*path_to_f;
	char			*absolute;
	char			*absocmd;
	struct dirent	*file;

	i = 0;
	absolute = take_dir((char *)(*cmdword)->value);
	if (absolute)
		absocmd = take_absocmd((char *)(*cmdword)->value);
	else
		absocmd = NULL;
	while (paths[i])
	{
		if (absolute)
			data->dir = opendir(absolute);
		else
			data->dir = opendir(paths[i]);
		file = readdir(data->dir);
		while (file)
		{
			if ((absocmd && !ft_strcmp(absocmd, file->d_name))
				|| !ft_strcmp((*cmdword)->value, file->d_name))
			{
				path_to_f = ft_strjoin(paths[i], "/");
				path_to_f = ft_strsjoin(path_to_f, file->d_name);
				if (absocmd)
				{
					free(path_to_f);
					path_to_f = ft_strdup((char *)(*cmdword)->value);
					free((char *)(*cmdword)->value);
					(*cmdword)->value = ft_strdup(absocmd);
				}
				if (is_an_execbin(path_to_f))
					return (free(absolute), free(absocmd), path_to_f);
			}
			file = readdir(data->dir);
		}
		i++;
		closedir(data->dir);
		data->dir = NULL;
	}
	free(absolute);
	free(absocmd);
	return (NULL);
}

char	*getcmdpath(t_token **cmdline, t_data *data)
{
	char	*path;
	char	**paths;
	t_token	*cmd;

	cmd = *cmdline;
	while (cmd && !is_sep_toktype(*cmd) && cmd->type != Command)
		cmd = cmd->next;
	if (!cmd || !cmd->value || cmd->type != Command)
		return (NULL);
	path = getenvval("PATH", data->env);
	paths = ft_split(path, ':');
	free(path);
	if (!paths)
		return (NULL);
	path = check_in_path(cmdline, data, paths);
	dfree((void **)paths);
	return (path);
}

char	*catch_execbin(t_token *cmdline)
{
	char			*path;
	DIR				*dir;
	struct dirent	*rdir;

	while (cmdline && !is_sep_toktype(*cmdline) && cmdline->type != Command)
		cmdline = cmdline->next;
	if (!cmdline || !cmdline->value || cmdline->type != Command)
		return (NULL);
	if (ft_strncmp(cmdline->value, "./", 2))
		return (NULL);
	path = NULL;
	dir = opendir(".");
	rdir = readdir(dir);
	while (rdir)
	{
		if (!ft_strcmp(&cmdline->value[2], rdir->d_name))
			path = ft_strdup(&cmdline->value[2]);
		rdir = readdir(dir);
	}
	return (closedir(dir), path);
}
