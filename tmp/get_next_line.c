/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:29:45 by cachetra          #+#    #+#             */
/*   Updated: 2024/07/18 00:20:52 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.h"

ssize_t	gnl_read_once(int fd, char **sbuf)
{
	ssize_t	b_read;

	b_read = read(fd, *sbuf, BUFFER_SIZE);
	if (b_read < 0)
		return (free(*sbuf), ERROR);
	(*sbuf)[b_read] = '\0';
	return (b_read);
}

ssize_t	gnl_read_chunk(int fd, char **bbuf)
{
	char	*tmp;
	char	*bbuf_tmp;
	ssize_t	b_read;
	ssize_t	b_read_tot;

	gnl_init(*bbuf, BUFFER_SIZE);
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (ERROR);
	b_read = BUFFER_SIZE;
	b_read_tot = 0;
	while (b_read == BUFFER_SIZE)
	{
		b_read = gnl_read_once(fd, &tmp);
		if (b_read == ERROR)
			return (gnl_free_null(bbuf), ERROR);
		b_read_tot += b_read;
		bbuf_tmp = *bbuf;
		*bbuf = gnl_strjoin(bbuf_tmp, tmp);
		free(bbuf_tmp);
		if (gnl_strlen_till(*bbuf, '\n') != NOT_FOUND)
			break ;
	}
	free(tmp);
	return (b_read_tot);
}

char	*gnl_get_line(char **mem, char *buf)
{
	ssize_t	i;
	ssize_t	nl_pos;
	char	*tmp;
	char	*rtn;

	tmp = gnl_strjoin(*mem, buf);
	if (!tmp)
		return (free(*mem), NULL);
	gnl_free_null(mem);
	nl_pos = gnl_strlen_till(tmp, '\n');
	if (nl_pos == NOT_FOUND)
		return (tmp);
	rtn = gnl_strndup(tmp, nl_pos + 1);
	if (!rtn)
		return (free(tmp), NULL);
	if (tmp[nl_pos + 1] == '\0')
		return (free(tmp), rtn);
	*mem = (char *)malloc(sizeof(char) * (gnl_strlen_till(tmp, 0) - nl_pos));
	if (!(*mem))
		return (free(tmp), free(rtn), NULL);
	i = nl_pos;
	while (tmp[++i])
		(*mem)[i - nl_pos - 1] = tmp[i];
	(*mem)[i - nl_pos - 1] = '\0';
	return (free(tmp), rtn);
}

char	*get_next_line(int fd)
{
	static char	*mem;
	char		*rtn;
	char		*tmp;
	ssize_t		b_read;

	if (fd < 0 || fd >= MAX_FD_COUNT || BUFFER_SIZE <= 0)
		return (NULL);
	rtn = NULL;
	tmp = NULL;
	if (gnl_strlen_till(mem, '\n') != NOT_FOUND)
	{
		rtn = gnl_get_line(&mem, tmp);
		return (rtn);
	}
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (gnl_free_null(&mem), NULL);
	b_read = gnl_read_chunk(fd, &tmp);
	if (b_read == ERROR)
		return (gnl_free_null(&mem), NULL);
	else if (b_read || !(((mem && !mem[0]) || !mem)))
		rtn = gnl_get_line(&mem, tmp);
	return (free(tmp), rtn);
}
