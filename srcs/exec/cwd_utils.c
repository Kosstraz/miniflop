/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:17:28 by bama              #+#    #+#             */
/*   Updated: 2024/08/06 20:09:11 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Sur "/bin/ls" récupère "/bin/"
// Sur "DEV/cursus/3/ez/minishell" récupère "DEV/cursus/3/ez/"
char	*take_dir(char *path_to_file)
{
	char	**words;
	char	*dir;
	char	isdir;
	size_t	i;

	isdir = 0;
	i = 0;
	dir = NULL;
	while (path_to_file[i])
		if (path_to_file[i++] == '/')
			isdir = 1;
	if (!isdir)
		return (NULL);
	i = 0;
	words = ft_split(path_to_file, '/');
	if (!words)
		return (NULL);
	if (path_to_file[0] == '/')
		dir = ft_strsjoin(dir, "/");
	while (words[i] && words[i + 1])
	{
		dir = ft_strsjoin(dir, words[i++]);
		dir = ft_strsjoin(dir, "/");
	}
	return (dfree((void **)words), dir);
}

// Sur "/bin/ls" récupère "ls"
// Sur "DEV/cursus/3/ez/minishell" récupère "minishell"
char	*take_absocmd(char	*path_to_file)
{
	char	**words;
	char	*ret;
	size_t	i;

	i = 0;
	ret = NULL;
	words = ft_split(path_to_file, '/');
	if (!words)
		return (NULL);
	while (words[i] && words[i + 1])
		i++;
	if (words[i] && !words[i + 1])
		ret = ft_strdup(words[i]);
	dfree((void **)words);
	return (ret);
}
