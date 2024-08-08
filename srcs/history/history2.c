/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:25:57 by bama              #+#    #+#             */
/*   Updated: 2024/08/08 22:08:43 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_history_fpath(t_data *data)
{
	char	*user;
	char	*hpath;

	user = getenvval("USER", data->env);
	hpath = ft_strdup("/home/");
	hpath = strljoin(hpath, user);
	hpath = strljoin(hpath, HISTORY_PATH);
	free(user);
	return (hpath);
}
