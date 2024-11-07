/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:13:33 by cachetra          #+#    #+#             */
/*   Updated: 2024/11/06 17:03:56 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**abc_sort_env(t_env *env)
{
	char	**strsenv;

	size_t	size;
	size_t	i;
	size_t	j;

	strsenv = convert_env(env);
	if (!strsenv)
		return (NULL);
	i = 0;
	while (strsenv[i])
	{
		j = 0;
		while (strsenv[j])
		{
			size = ft_strlen(ft_strchr(strsenv[i], '='));
			if (size > ft_strlen(ft_strchr(strsenv[j], '=')))
				size = ft_strlen(ft_strchr(strsenv[j], '='));
			if (ft_strncmp(strsenv[i], strsenv[j], size) < 0)
				swap_addr((void **)&strsenv[i], (void **)&strsenv[j]);
			j++;
		}
		i++;
	}
	return (strsenv);
}

static void	print_abc_env(t_data *data, t_env *env)
{
	char	**sorted;
	size_t	i;

	i = 0;
	sorted = abc_sort_env(env);
	if (!sorted)
		exit_shell(NULL, data, 1);
	while (sorted[i])
		printf("%sexport%s %s\n", BOLD, RESET, sorted[i++]);
}

int	ft_export(char **args, t_data *data)
{
	if (!args || !args[1])
		print_abc_env(data, data->env);
	else if (!export_args(args, &data->env))
		exit_shell("\e[1;31mmalloc\e[0m", data, EXIT_FAILURE);
	data->ret_cmd = SUCCESS;
	return (0);
}
