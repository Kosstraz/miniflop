/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:13:33 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/04 14:25:39 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **args, t_data *data)
{
	int		size;
	t_env	*env;
	char	**strs;

	size = 0;
	env = data->env->next;
	if (!args[1])
	{
		ft_printf("ez\n");
	}
	else if (!export_args(args, &data->env))
		exit_shell("\e[1;31mmalloc\e[0m", data, EXIT_FAILURE);
	print_env(data->env);
	// dfree((void **)args);
	data->ret_cmd = 0;
	return (0);
}
