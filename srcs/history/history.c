/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:49:48 by bama              #+#    #+#             */
/*   Updated: 2024/08/10 00:14:46 by bama             ###   ########.fr       */
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
	char	*trunc;

	hpath = get_history_fpath(data);
	data->historyfd = open_hfile(data);
	history = cat(hpath, O_CREAT | O_RDWR, 0666);
	close_hfile(data);
	hdoc = heredoc(hpath, O_CREAT | O_RDWR, 0666, '\n');
	if (line[0] && chrocc(line, ' ') != ft_strlen(line) && ft_strcmp(line, hdoc))
	{
		trunc = strtrunc_quotes(line, ' ');
		tmp = strljoin(trunc, "\n");
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
	char	*trunc;
	int		fd;

	fd = open_hfile(data);
	hpath = get_history_fpath(data);
	trunc = strtrunc_quotes(line, ' ');
	hdoc = get_next_line(fd);
	while (hdoc)
	{
		if (!ft_strcmp(trunc, hdoc))
			return (close_hfile(data), hdoc);
		free(hdoc);
		hdoc = get_next_line(fd);
	}
	close_hfile(data);
	free(hpath);
	return (NULL);
}
