/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:36:30 by bama              #+#    #+#             */
/*   Updated: 2024/07/22 23:03:18 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **env);
void	add_env_to_data(t_data *data, char **env);
void	free_data(t_data *data);
void	print_linked_list(t_env *env);

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	// minishell(env);
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	add_env_to_data(&data, env);
	print_linked_list(data.env);
	free_data(&data);
	return (0);
}
