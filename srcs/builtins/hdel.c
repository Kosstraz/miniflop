/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdel.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:49:57 by bama              #+#    #+#             */
/*   Updated: 2024/08/10 01:13:49 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hdel(char **arguments, t_data *data)
{
	char	*hpath;

	(void)arguments;
	hpath = get_history_fpath(data);
	if (access(hpath, F_OK) == -1)
	{
		write(2, HDEL_EXIST, ft_strlen(HDEL_EXIST));
		data->ret_cmd = ERROR;
		return (ERROR);
	}
	data->historyfd = open(hpath, O_WRONLY | O_TRUNC, 0666);
	free(hpath);
	if (data->historyfd < 0)
	{
		write(2, HDEL_ERROR, ft_strlen(HDEL_ERROR));
		data->ret_cmd = ERROR + 1;
		return (ERROR + 1);
	}
	close(data->historyfd);
	data->historyfd = -1;
	write(1, HDEL_SUCCESS, ft_strlen(HDEL_SUCCESS));
	data->ret_cmd = SUCCESS;
	return (SUCCESS);
}
