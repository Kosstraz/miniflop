/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:17:28 by bama              #+#    #+#             */
/*   Updated: 2024/08/08 14:35:16 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_twice(char *str, char sep1, char sep2)
{
	char	*first;
	char	**tmp;
	char	**rtn;

	if (!str)
		return (NULL);
	tmp = ft_split(str, sep1);
	if (!tmp)
		return (NULL);
	first = ft_strdup(tmp[0]);
	dfree((void **)tmp);
	if (!first)
		return (NULL);
	rtn = ft_split(first, sep2);
	free(first);
	return (rtn);
}

static char	*take_dir_no_space2(char *path_to_file, char **words)
{
	int		i;
	char	*dir;

	i = 0;
	dir = NULL;
	if (path_to_file[0] == '/')
		dir = ft_strsjoin(dir, "/");
	while ((words[i] && words[i + 1]) || i == 0)
	{
		dir = ft_strsjoin(dir, words[i++]);
		dir = ft_strsjoin(dir, "/");
	}
	return (dir);
}

char	*take_dir_no_space(char *path_to_file)
{
	char	**words;
	char	*dir;
	char	isdir;
	size_t	i;

	isdir = 0;
	i = 0;
	dir = NULL;
	if (!ft_strchr(path_to_file, '/'))
		return (NULL);
	while (path_to_file[i])
		isdir += (path_to_file[i++] == '/');
	if (!isdir)
		return (NULL);
	if (path_to_file[0] == '/')
		dir = ft_strsjoin(dir, "/");
	words = split_twice(path_to_file, ' ', '/');
	i = 0;
	while (words && ((words[i] && words[i + 1]) || (i == 0 && words[i])))
	{
		dir = ft_strsjoin(dir, words[i++]);
		dir = ft_strsjoin(dir, "/");
	}
	return (dfree((void **)words), dir);
}

char	*take_absocmd_no_space(char	*path_to_file, t_data *data)
{
	char	**words;
	char	*ret;
	size_t	len;
	size_t	i;

	i = 0;
	ret = NULL;
	if (!path_to_file[0] || !ft_strcmp(path_to_file, "/"))
		return (NULL);
	// if (!ft_strchr(path_to_file, '/'))
	// 	return (ft_strdup(path_to_file));
	words = ft_split(path_to_file, '/');
	if (!words)
		return (NULL);
	// if (words[0] && !words[1] && !ft_strchr(path_to_file, '/'))
	// 	return (dfree((void **)words), ft_strdup(path_to_file));
	if (words[0] && !words[1] && ft_strchr(path_to_file, '/'))
		return (dfree((void **)words), NULL);
	while (words[i] && words[i + 1])
		i++;
	len = 0;
	while (words[i][len] && words[i][len] != ' ')
		len++;
	if (len)
	{
		ret = (char *)ft_malloc(sizeof(char) * (len + 1), data);
		ft_memmove(ret, words[i], len);
		ret[len] = '\0';
	}
	dfree((void **)words);
	return (ret);
}
