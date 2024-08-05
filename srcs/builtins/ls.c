/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:19:33 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/05 22:14:59 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define NONE	"\e[0m"
# define RED	"\e[1;31m"
# define GREEN	"\e[1;32m"
# define BLUE	"\e[1;34m"

# ifndef DT_UNKNOWN
#  define DT_UNKNOWN	0
# endif

# ifndef DT_DIR
#  define DT_DIR		8
# endif

# ifndef DT_REG
#  define DT_REG		10
# endif

void	aff_dir_colors(unsigned char type, char *name)
{
	if (type == DT_DIR)
		write(STDOUT_FILENO, BLUE, 7);
	else if (type == DT_REG && is_a_execbin(ft_strdup(name)))
		write(STDOUT_FILENO, GREEN, 7);
	else if (type == DT_REG)
		write(STDOUT_FILENO, NONE, 4);
	else if (type == DT_UNKNOWN)
		write(STDOUT_FILENO, RED, 7);
}

void	show_dir_contents(char *filename, char *ref, t_data *data)
{
	int				cnt;
	DIR				*dir;
	struct dirent	*dirent;

	cnt = 1;
	dir = opendir(filename);
	if (!dir)
		exit_shell("\e[31mopendir\e[0m", data, EXIT_FAILURE);
	dirent = readdir(dir);
	while (dirent)
	{
		aff_dir_colors(dirent->d_type, dirent->d_name);
		if (!ref || !ft_strncmp(ref, dirent->d_name, ft_strlen(ref)))
		{
			write(STDOUT_FILENO, dirent->d_name, ft_strlen(dirent->d_name));
			if (cnt % 5)
				write(STDOUT_FILENO, "\t", 1);
			else
				write(STDOUT_FILENO, "\n", 1);
		}
		dirent = readdir(dir);
	}
	closedir(dir);
}

int	ft_ls(char **args, t_data *data)
{
	int	cnt;

	cnt = 0;
	while (args[cnt + 1])
		cnt++;
	dfree((void **)args);
}
