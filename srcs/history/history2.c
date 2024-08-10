/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:25:57 by bama              #+#    #+#             */
/*   Updated: 2024/08/10 02:04:31 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*up_history(char *line, t_data *data)
{
	char	*trunc;
	char	*gnl;

	data->historyfd = open_hfile(data);
	if (!line || chrocc(line, ' ') == ft_strlen(line)
		|| ft_strlen(line) <= 0)
		return (close_hfile(data), get_next_line(data->historyfd));
	trunc = strtrunc_quotes(line, ' ');
	gnl = get_next_line(data->historyfd);
	if (!ft_strncmp(gnl, trunc, ft_strlen(trunc)))
	{
		close_hfile(data);
		free(trunc);
		return (gnl);
	}
	close_hfile(data);
	free(gnl);
	free(trunc);
	return (NULL);
}

char	*get_history_fpath(t_data *data)
{
	char	*user;
	char	*hpath;

	user = getenvval("USER", data->env);
	hpath = ft_strdup("/home/");
	hpath = strlljoin(hpath, user);
	hpath = strljoin(hpath, HISTORY_PATH);
	return (hpath);
}
