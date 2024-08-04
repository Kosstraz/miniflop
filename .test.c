/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 02:56:15 by bama              #+#    #+#             */
/*   Updated: 2024/08/04 14:57:39 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/gnl/get_next_line_bonus.h"
#include ".test.h"
#include <fcntl.h>
#include <stdio.h>

void	reopenf(struct s_openf *openfile)
{
	close(openfile->fd);
	*openfile = openf(openfile->file_path ,openfile->oflags, openfile->mode);
}

static size_t	get_nb_of_line_in_fd(int fd)
{
	char	*gnl;
	size_t	count;

	count = 0;
	gnl = get_next_line(fd);
	while (gnl)
	{
		count++;
		printf("\e[32m%s\e[0m\n", gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
	return (count);
}

// Obtenir la n-ième dernière ligne d'un fichier
// Si n=0 la dernière ligne sera retournée
// Si n=3 la 3ème avant dernière ligne sera retournée
// Si n>[contenu du fd] la première ligne sera tjrs retournée
char	*ft_ntail(struct s_openf *openfile, int n)
{
	char	*ret;
	char	*gnl;
	size_t	i;
	size_t	size;

	reopenf(openfile);
	size = get_nb_of_line_in_fd(openfile->fd);
	printf("size %d\n", size);
	reopenf(openfile);
	gnl = get_next_line(openfile->fd);
	if (n + 1 > size)
		return (gnl);
	i = 0;
	while (gnl && i < size - n - 1)
	{
		free(gnl);
		gnl = get_next_line(openfile->fd);
		i++;
	}
	return (gnl);
}

void	closef(struct s_openf *openfile)
{
	free((char *)openfile->file_path);
	openfile->oflags = 0;
	openfile->mode = 0;
	close(openfile->fd);
}

struct s_openf	openf(const char *filepath, int oflags, int mode)
{
	struct s_openf	openfile;

	openfile.file_path = filepath;
	openfile.oflags = oflags;
	openfile.mode = mode;
	openfile.fd = open(filepath, oflags, mode);
	return (openfile);
}

int	main(void)
{
	struct	s_openf	openfile;
	char			*ntail;

	openfile = openf("LS", O_RDONLY, 0666);
	ntail = ft_ntail(&openfile, 0);
	if (ntail)
		printf("%s\n", ntail);
	else
		printf("(null)\n");

	ntail = ft_ntail(&openfile, 1);
	if (ntail)
		printf("%s\n", ntail);
	else
		printf("(null)\n");

	ntail = ft_ntail(&openfile, 0);
	if (ntail)
		printf("%s\n", ntail);
	else
		printf("(null)\n");
	return (0);
}
