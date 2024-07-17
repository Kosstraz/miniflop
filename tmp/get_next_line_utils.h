/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:45:54 by cachetra          #+#    #+#             */
/*   Updated: 2024/06/08 17:46:10 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_UTILS_H
# define GET_NEXT_LINE_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# define MAX_FD_COUNT	1024

# define NOT_FOUND	-1
# define ERROR		-2

/* UTILS */

void	gnl_init(char *s, ssize_t s_size);
void	gnl_free_null(char **ptr);

ssize_t	gnl_strlen_till(char *str, char c);

char	*gnl_strndup(char *src, ssize_t n);
char	*gnl_strjoin(char *s1, char *s2);

/* FONCTIONS PRINCIPALES */

ssize_t	gnl_read_once(int fd, char **sbuf);
ssize_t	gnl_read_chunk(int fd, char **bbuf);

char	*gnl_get_line(char **mem, char *buf);

#endif
