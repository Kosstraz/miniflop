/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datas_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:01:07 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 23:03:38 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_to_datas(t_data *datas, char **env)
{
	/*
		Carla ma femme, créer une liste chaînée pour stocker chaque
		variable d'environnement (et stocke les). Dans ce style :
		char	*name
		char	*value
		struct	*next
	*/
}

void	free_datas(t_data *datas)
{
	free_tokens(&datas->tokens);
}

void	init_datas(t_data *datas)
{
	datas->tokens = NULL;
	datas->command_ret = 0;
	datas->_errcode = 0;
}
