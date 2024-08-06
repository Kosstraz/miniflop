/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:30:32 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/06 23:28:17 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// [TAB] to do
// tab sans rien												- OK
// regler le nb de '\n' avec cas part. de la derniere ligne
// bouger le ez avec les fleches
// init tab function											- OK
// regler le "/"
// selectionner le ez
// modifier les fonctions ez

#include "minishell.h"

static void	print_files_colors(unsigned char type, char *name)
{
	if (type == DIRECTORY)
		write(STDOUT_FILENO, BLUE, 5);
	else if (type == REG_FILE && is_an_execbin(ft_strdup(name)))
		write(STDOUT_FILENO, GREEN, 5);
	else if (type == REG_FILE)
		write(STDOUT_FILENO, RESET, 4);
	else if (type == F_UNKNOWN)
		write(STDOUT_FILENO, RED, 5);
}

void	print_files(t_tab *tab)
{
	int	len;
	int	printed;

	printed = 0;
	write(1, "\n", 1);
	while (printed < tab->cnt)
	{
		print_files_colors(tab->types[printed], tab->files[printed]);
		len = ft_strlen(tab->files[printed]);
		write(1, tab->files[printed], len);
		while (len++ < tab->max_len)
			write(1, " ", 1);
		if (++printed % tab->max_cnt == 0)
			write(1, "\n", 1);
	}
}

void	key_tab(t_data *data)
{
	if (!data->term.tab.is_on)
		enter_tab_mode(data);
	if (data->term.tab.pos++ == -1)
		print_files(&data->term.tab);
}
