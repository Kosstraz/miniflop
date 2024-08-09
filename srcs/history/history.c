/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:49:48 by bama              #+#    #+#             */
/*   Updated: 2024/08/09 02:05:45 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_hfile(t_data *data)
{
	char	*hpath;
	int		fd;

	hpath = get_history_fpath(data);
	fd = open(hpath, O_CREAT | O_RDWR, 0666);
	free(hpath);
	return (fd);
}


// close(data->historyfd)
// data->historyfd = -1;
inline void	close_hfile(t_data *data)
{
	close(data->historyfd);
	data->historyfd = -1;
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

void	add_to_history(char *line, t_data *data)
{
	char	*history;
	char	*hdoc;
	char	*tmp;
	char	*hpath;

	hpath = get_history_fpath(data);
	data->historyfd = open_hfile(data);
	history = cat(hpath, O_CREAT | O_RDWR, 0666);
	close_hfile(data);
	hdoc = heredoc(hpath, O_CREAT | O_RDWR, 0666, '\n');
	if (line[0] && chrocc(line, ' ') != ft_strlen(line) && ft_strcmp(line, hdoc))
	{
		tmp = ft_strjoin(line, "\n");
		history = strlljoin(tmp, history);
		data->historyfd = open_hfile(data);
		write(data->historyfd, history, ft_strlen(history));
		close_hfile(data);
	}
	free(hpath);
	free(hdoc);
	free(history);
}

char	*search_in_history(char *line, t_data *data)
{
	char	*hdoc;
	char	*hpath;

	hpath = get_history_fpath(data);
	hdoc = heredoc(hpath, O_CREAT | O_RDWR, 0666, '\n');
	while (hdoc)
	{
		if (!ft_strncmp(line, hdoc, ft_strlen(line)))
			return (hdoc);
		free(hdoc);
		hdoc = heredoc(hpath, O_CREAT | O_RDWR, 0666, '\n');
	}
	free(hpath);
	return (NULL);
}
