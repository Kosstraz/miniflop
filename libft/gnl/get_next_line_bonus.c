/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:57:35 by ymanchon          #+#    #+#             */
/*   Updated: 2024/07/18 16:11:19 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line_bonus.h"

// @param buffer la chaine qui sera analysee
// @param bef ptr sur chaine qui contiendra tout avant 'c' ('c' compris)
// @param aft ptr sur chaine qui contiendra tout apres 'c' ('c' non compris)
void	subdivstr(const char *buffer, char **bef, char **aft, char c);
// Save line || subdivstr_bef
char	*save_line(const char *buffer, char c);
// Save after-line content || subdivstr_aft
// @param buffer sera free et NULL
char	*save_after_c(char **buffer, char c);

void	subdivstr(const char *buffer, char **bef, char **aft, char c)
{
	char	*b;
	char	*a;

	a = (char *)buffer;
	b = save_line(buffer, c);
	a = save_after_c(&a, c);
	if (bef)
		*bef = b;
	else
		free_n(&b);
	if (aft)
		*aft = a;
	else
		free_n(&a);
}

char	*save_after_c(char **buffer, char c)
{
	size_t	i;
	size_t	bef_size;
	size_t	aft_size;
	char	*tmp;
	char	*ret;

	tmp = *buffer;
	if (!tmp)
		return (NULL);
	bef_size = ft_strlenc(tmp, c);
	aft_size = ft_strlenc(tmp, '\0') - bef_size;
	ret = (char *)malloc(sizeof(char) * (aft_size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (tmp[bef_size])
		ret[i++] = tmp[bef_size++];
	ret[i] = '\0';
	free_n(buffer);
	return (ret);
}

char	*save_line(const char *buffer, char c)
{
	size_t	i;
	size_t	bef_size;
	char	*ret;

	if (!buffer)
		return (NULL);
	bef_size = ft_strlenc(buffer, c);
	ret = (char *)malloc(sizeof(char) * (bef_size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < bef_size - 1)
	{
		ret[i] = buffer[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	gnl_read(int fd, char **ret, char **buffer)
{
	int	i;

	*ret = (char *)malloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	if (!(*ret))
		return (free_n(buffer), -1);
	i = read(fd, *ret, GNL_BUFFER_SIZE);
	if (i < 0)
		return (free_n(ret), free_n(buffer), -1);
	(*ret)[i] = '\0';
	if (!i && buffer && *buffer && (*buffer)[0])
	{
		free_n(ret);
		*ret = save_line(*buffer, '\n');
		*buffer = save_after_c(buffer, '\n');
		return (1);
	}
	else if (!i)
	{
		free_n(buffer);
		free_n(ret);
		return (-1);
	}
	*buffer = ft_strjoin_free(*buffer, *ret);
	free_n(ret);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*ret;
	char		log;

	ret = NULL;
	if (fd < 0)
		return (free_n(&(buffer)));
	while (!thereis_nl(buffer))
	{
		log = gnl_read(fd, &ret, &(buffer));
		if (log < 0)
			return (NULL);
		else if (log > 0)
			return (ret);
	}
	free_n(&ret);
	ret = save_line(buffer, '\n');
	buffer = save_after_c(&(buffer), '\n');
	if (!buffer[0])
		free_n(&(buffer));
	return (ret);
}

//#include <fcntl.h>
//#include <stdio.h>
//#define LINE_COUNT 3
//#define FILE_NAME "test.txt"

/*int	main(void)
{
	int fd = open(FILE_TEST, O_RDONLY);
	char *gnl = NULL;

	for (int i = 0; i++ < COUNT_TEST ;)
	{
		gnl = get_next_line(fd);
		printf("\e[31mGNL : %s\e[0m$\n", gnl);
		free(gnl);
	}

	close(fd);
	return (0);
}*/
