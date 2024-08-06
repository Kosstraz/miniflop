/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:49:48 by bama              #+#    #+#             */
/*   Updated: 2024/08/07 01:19:21 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_hfile(void)
{
	return (open(HISTORY_PATH, O_CREAT | O_TRUNC | O_RDWR, 0666));
}

void	create_history(t_data *data)
{
	data->historyfd = open_hfile();
}

void	add_to_history(char *line, t_data *data)
{
	char	*history;

	history = cat(data->historyfd);
	history = ft_strsjoin(line, history);
	write(data->historyfd, history, ft_strlen(history));
	free(history);
}

char	*search_in_history(char *line, t_data *data)
{
	
}
