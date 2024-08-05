/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handling3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:39:06 by bama              #+#    #+#             */
/*   Updated: 2024/08/05 20:13:56 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	ft_memset(data->fildes, 0, 2);
	g_sig = 0;
	data->npid = 0;
	data->dir = opendir(".");
	data->tokens = NULL;
	data->_errcode = 0;
	data->fileno[0] = -1;
	data->fileno[1] = -1;
	data->fileno[2] = -1;
}
