/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:24:47 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/06 20:01:51 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// srcs/exec/search_cmd.c:71:21: warning: the comparison will always evaluate as ‘true’ for the address of ‘d_name’ will never be NULL [-Waddress]
//    71 |         while (rdir && rdir->d_name)


#include "minishell.h"

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
