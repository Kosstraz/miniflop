/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:25:57 by bama              #+#    #+#             */
/*   Updated: 2024/11/17 16:42:27 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*up_history_saved(char *line, t_data *data);

char	*up_history(char *line, t_data *data)
{
	char	*trunc;
	char	*gnl;

	(void)data;
	if (data->history.current_line < data->history.nb_of_line_searched - 1)
		return (up_history_saved(line, data));
	data->historyfd = open_hfile(data);
	if (!line || chrocc(line, ' ') == ft_strlen(line)
		|| ft_strlen(line) <= 0)
	{
		gnl = get_next_line(data->historyfd);
		new_history_info_node(data, &data->history.info, gnl);
		data->history.current_line++;
		data->history.nb_of_line_searched++;
		return (close_hfile(data), gnl);
	}
	trunc = strtrunc_quotes(line, ' ');
	gnl = get_next_line(data->historyfd);
	if (!ft_strncmp(gnl, trunc, ft_strlen(trunc)))
	{
		close_hfile(data);
		free(trunc);
		new_history_info_node(data, &data->history.info, gnl);
		data->history.current_line++;
		data->history.nb_of_line_searched++;
		return (gnl);
	}
	close_hfile(data);
	free(gnl);
	free(trunc);
	return (NULL);
}

char	*up_history_saved(char *line, t_data *data)
{
	t_history	*node;
	ssize_t		i;

	(void)data;
	i = 0;
	if (data->history.nb_of_line_searched > 0)
	{
		node = data->history.info;
		while (node && node->next && node->next->line
			&& i++ < data->history.current_line)
			node = node->next;
		data->history.current_line++;
		return (node->line);
	}
	return (NULL);
}

char	*down_history(char *line, t_data *data)
{
	t_history	*node;
	ssize_t		i;

	i = 0;
	if (data->history.nb_of_line_searched > 0 && data->history.current_line > 0)
	{
		node = data->history.info;
		while (node && node->next && node->next->line
			&& i++ < data->history.current_line + 1)
			node = node->next;
		data->history.current_line--;
		return (node->line);
	}
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

void	free_history_info(t_data *data)
{
	t_history	*tmp;
	t_history	*node;

	if (!data->history.info)
		return ;
	node = data->history.info->next;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp->line);
		free(tmp);
	}
	free(data->history.info->line);
	free(data->history.info);
}

void	new_history_info_node(t_data *data, t_history **history, char *gnl)
{
	t_history	*first;

	first = *history;
	while (*history)
		*history = (*history)->next;
	*history = (t_history *)malloc(sizeof(t_history));
	if (!*history)
		return (exit_shell("malloc", data, BAD_MALLOC));
	(*history)->line = gnl;
	(*history)->next = NULL;
	if (first)
		*history = first;
}
