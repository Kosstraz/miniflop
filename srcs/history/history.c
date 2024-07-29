/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:49:48 by bama              #+#    #+#             */
/*   Updated: 2024/07/28 22:43:47 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_history(t_data *data)
{
	data->historyfd = open(".miniflop.history",
			O_CREAT | O_APPEND | O_RDWR, 0777);
}

