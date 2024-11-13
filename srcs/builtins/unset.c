/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:40:25 by bama              #+#    #+#             */
/*   Updated: 2024/11/13 15:29:09 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_notfound(char *varname)
{
	write(2, UNSET_NOT_FOUND1, ft_strlen(UNSET_NOT_FOUND1));
	write(2, varname, ft_strlen(varname));
	write(2, UNSET_NOT_FOUND2, ft_strlen(UNSET_NOT_FOUND2));
}

static char	find_envvar(char *varname, t_data *data)
{
	t_env	*prev;
	t_env	*env;

	prev = NULL;
	env = data->env;
	if (!ft_strcmp(varname, "?"))
		return (ft_printf("%s%s", UNSET_IDENTIFIER1, UNSET_IDENTIFIER2));
	while (env)
	{
		if (!ft_strcmp(env->name, varname))
		{
			if (prev)
				prev->next = env->next;
			else
				data->env = data->env->next;
			free(env->value);
			free(env->name);
			free(env);
			return (1);
		}
		prev = env;
		env = env->next;
	}
	print_notfound(varname);
	return (0);
}

int	ft_unset(char **arguments, t_data *data)
{
	size_t	i;

	i = 1;
	while (arguments[i])
		find_envvar(arguments[i++], data);
	data->ret_cmd = SUCCESS;
	return (0);
}
