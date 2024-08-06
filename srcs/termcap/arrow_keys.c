/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:24:47 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/06 18:07:20 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		write(STDOUT_FILENO, BLUE, 5);
	else if (type == DT_REG && is_a_execbin(ft_strdup(name)))
		write(STDOUT_FILENO, GREEN, 5);
	else if (type == DT_REG)
		write(STDOUT_FILENO, RESET, 4);
	else if (type == DT_UNKNOWN)
		write(STDOUT_FILENO, RED, 5);
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
		if (!ref || !ft_strncmp(ref, dirent->d_name, ft_strlen(ref) - 1))
		{
			write(STDOUT_FILENO, dirent->d_name, ft_strlen(dirent->d_name));
			if (cnt++ % 5)
				write(STDOUT_FILENO, "\t", 1);
			else
				write(STDOUT_FILENO, "\n", 1);
		}
		dirent = readdir(dir);
	}
	closedir(dir);
}

void	key_tab(t_data *data)
{
	int		i;
	int		n;
	char	*tmp;
	char	*ref;

	n = data->term.curs.l;
	// i = data->term.line.i;
	// while (i > 1 && data->term.line.buf[i] != ' '
	// 	&& data->term.line.buf[i] != '\t')
	// 		i--;
	i = data->term.line.i - 1 + (data->term.line.i == 0);
	while (data->term.line.buf[i] == ' ' || data->term.line.buf[i] == '\t')
		i--;
	while (data->term.line.buf[i] && data->term.line.buf[i] != ' '
		&& data->term.line.buf[i] != '\t')
		i--;
	ref = ft_strdup(&data->term.line.buf[i + 1 - (i == 0)]);
	ft_printf("\n\n%s\n", ref);
	// if (!tmp)
	// 	ref = ft_strdup(data->term.line.buf);
	// else
	// 	ref = ft_strdup(tmp);
	if (!ref)
		exit_shell("\e[31mft_strdup\e[0m", data, EXIT_FAILURE);
	write(data->term.fd, data->term.caps.save.cap,
		data->term.caps.save.len);
	while (n++ <= data->term.line.last.l)
		write(data->term.fd, "\n", 1);
	show_dir_contents(".", ref, data);
	write(data->term.fd, data->term.caps.restore.cap,
		data->term.caps.restore.len);
}

void	key_up(t_data *data)
{
	if (data)
		write(2, "UP\n", 3);
}

void	key_down(t_data *data)
{
	if (data)
		write(2, "DOWN\n", 5);
}

void	key_right(t_data *data)
{
	if (!data->term.line.next)
		return ;
	if (data->term.curs.c != data->term.caps.cols)
		write(data->term.fd, data->term.caps.right.cap, data->term.caps.right.len);
	else
		move_down(&data->term, 0);
	data->term.line.i++;
	data->term.line.next--;
	update_position(&data->term, RIGHT);
}

void	key_left(t_data *data)
{
	if (!data->term.line.i)
		return ;
	if (data->term.curs.c != 1)
		write(data->term.fd, data->term.caps.left.cap, data->term.caps.left.len);
	else
		move_up(data, 1);
	data->term.line.i--;
	data->term.line.next++;
	update_position(&data->term, LEFT);
}
