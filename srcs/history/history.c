/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:49:48 by bama              #+#    #+#             */
/*   Updated: 2024/08/07 13:59:53 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_hfile(void)
{
	return (open(HISTORY_PATH, O_CREAT | O_RDWR, 0666));
}

static char	*heredoc(char *filepath, int oflags, int mode, char sep)
{
	char	*contant;
	char	c;
	int		fd;
	size_t	size;

	size = 0;
	fd = open(filepath, oflags, mode);
	while (read(fd, &c, 1) > 0 && c != sep)
		size++;
	close(fd);
	fd = open(filepath, oflags, mode);
	contant = (char *)malloc(sizeof(char) * (size + 1));
	if (!contant)
		return (NULL);
	read(fd, contant, size);
	contant[size] = 0;
	close(fd);
	return (contant);
}

void	create_history(t_data *data)
{
	data->historyfd = open_hfile();
}

void	add_to_history(char *line, t_data *data)
{
	char	*history;
	char	*hdoc;
	char	*tmp;

	close(data->historyfd);
	data->historyfd = open_hfile();
	history = cat(HISTORY_PATH, O_CREAT | O_RDWR, 0666);
	close(data->historyfd);
	hdoc = heredoc(HISTORY_PATH, O_CREAT | O_RDWR, 0666, '\n');
	if (ft_strcmp(line, hdoc))
	{
		tmp = ft_strjoin(line, "\n");
		history = ft_strssjoin(tmp, history);
		data->historyfd = open_hfile();
		write(data->historyfd, history, ft_strlen(history));
	}
	free(hdoc);
	free(history);
}

char	*search_in_history(char *line, t_data *data)
{
	char	*hdoc;

	(void)data;
	hdoc = heredoc(HISTORY_PATH, O_CREAT | O_RDWR, 0666, '\n');
	while (hdoc)
	{
		if (!ft_strncmp(line, hdoc, ft_strlen(line)))
			return (hdoc);
		free(hdoc);
		hdoc = heredoc(HISTORY_PATH, O_CREAT | O_RDWR, 0666, '\n');
	}
	return (NULL);
}
