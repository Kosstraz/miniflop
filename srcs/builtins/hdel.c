/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdel.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:49:57 by bama              #+#    #+#             */
/*   Updated: 2024/08/08 17:44:00 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hdel(t_data *data)
{
	char	*hpath;

	hpath = get_history_fpath(data);
	if (access(hpath, F_OK) == -1)
	{
		write(2, HDEL_EXIST, ft_strlen(HDEL_EXIST));
		return (1);
	}
	data->historyfd = open(hpath, O_WRONLY | O_TRUNC, 0666);
	free(hpath);
	if (data->historyfd < 0)
	{
		write(2, HDEL_ERROR, ft_strlen(HDEL_ERROR));
		return (1);
	}
	close(data->historyfd);
	data->historyfd = -1;
	write(1, HDEL_SUCCESS, ft_strlen(HDEL_SUCCESS));
	return (0);
}