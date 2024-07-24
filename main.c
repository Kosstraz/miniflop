/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:36:30 by bama              #+#    #+#             */
/*   Updated: 2024/07/23 18:45:11 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tmp.h"

int	main(int ac, char **av, char **env)
{
	// (void)ac;
	// (void)av;
	// minishell(env);


	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	add_env_to_data(&data, env);
	initialise(&data.term);
	return (0);
}
