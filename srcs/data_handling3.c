/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handling3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 00:39:06 by bama              #+#    #+#             */
/*   Updated: 2024/08/06 23:30:35 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	ft_memset(data->fildes, 0, 2);
	data->npid = 0;
	data->dir = NULL;
	data->tokens = NULL;
	data->exec_next = 1;
	data->_errcode = 0;
	data->blt_val = 0;
	data->fileno[0] = -1;
	data->fileno[1] = -1;
	data->fileno[2] = -1;
}
