/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:17:28 by bama              #+#    #+#             */
/*   Updated: 2024/08/08 22:15:19 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fetch_dir_name2(int len, char *path, char **words)
{
	int		i;
	char	*rtn;

	i = 0;
	rtn = NULL;
	if (!words)
		return (NULL);
	if (path[0] == '/')
		rtn = ft_strdup("/");
	while (words[i] && words[i + 1])
	{
		rtn = strljoin(rtn, words[i++]);
		rtn = strljoin(rtn, "/");
	}
	if (words[i] && !words[i + 1] && path[len - 1] == '/')
	{
		rtn = strljoin(rtn, words[i]);
		rtn = strljoin(rtn, "/");
	}
	return (rtn);
}

char	*fetch_dir_name(char *path)
{
	int		len;
	char	*rtn;
	char	**words;

	len = 0;
	if (!path[0] || !ft_strchr(path, '/'))
		return (NULL);
	while (path[len] && path[len] != ' ' && path[len] != '\t')
		len++;
	if (!len)
		return (NULL);
	if (path[len])
		path = ft_strndup(path, len);
	len = ft_strlen(path);
	words = ft_split(path, '/');
	if (!words)
		return (NULL);
	rtn = fetch_dir_name2(len, path, words);
	dfree((void **)words);
	return (rtn);
}

static char	*fetch_file_name2(int len, char *path)
{
	int		i;
	char	*rtn;

	i = len;
	rtn = NULL;
	while (i && path[i] != '/')
		i--;
	if (path[i] == '/')
		i++;
	rtn = ft_strdup(&path[i]);
	return (rtn);
}

char	*fetch_file_name(char *path)
{
	int		len;
	char	*rtn;

	len = 0;
	if (!path[0] || !ft_strcmp(path, "/"))
		return (NULL);
	while (path[len] && path[len] != ' ' && path[len] != '\t')
		len++;
	if (!len)
		return (NULL);
	if (path[len])
		path = ft_strndup(path, len);
	if (!ft_strchr(path, '/'))
		return (ft_strdup(path));
	len = ft_strlen(path);
	if (path[--len] == '/')
		return (NULL);
	rtn = fetch_file_name2(len, path);
	return (rtn);
}
