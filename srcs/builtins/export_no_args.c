/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:14:36 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/03 22:07:31 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_env	*env_remove_node(t_env *node)
// {
// 	t_env	*rtn;

// 	if (!node)
// 		return (NULL);
// 	rtn = node->next;
// 	free(node->name);
// 	free(node->value);
// 	free(node);
// 	return (rtn);
// }

// static t_env	*env_find_lowest(t_env *env, int *last)
// {
// 	int		curr;
// 	int		lowest;
// 	t_env	*rtn;
// 	char	cmp[CHUNK];

// 	lowest = INT_MAX;
// 	ft_memset(&cmp, 1, CHUNK);
// 	while (env)
// 	{
// 		curr = ft_strcmp(cmp, env->name);
// 		if (curr < lowest && curr > *last)
// 		{
// 			lowest = curr;
// 			rtn = env;
// 		}
// 		env = env->next;
// 	}
// 	return (rtn);
// }

// static int	env_sort(t_env *env, char ***strs, int size)
// {
// 	int		i;
// 	int		last;
// 	t_env	*tmp;

// 	i = 0;
// 	last = 0;
// 	while (i < size - 1)
// 	{
// 		printf("%d\n", cnt++);
// 		tmp = env_find_lowest(env, &last);
// 		(*strs)[i] = ft_strdup(tmp->name);
// 		if (!(*strs)[i++])
// 			return (0);
// 		// tmp = env_remove_node(tmp);
// 	}
// 	return (1);
// }

// static int	export_print(t_env *env, char ***strs, int size)
// {
// 	int		i;
// 	t_env	*tmp;

// 	i = -1;
// 	if (!env)
// 		return (0);
// 	if (!env_sort(env, strs, size))
// 		return (0);
// 	for (int x; (*strs)[x]; x++)
// 		printf("%s\n", (*strs)[x]);
// 	exit(0);
// 	while (++i < size)
// 	{
// 		tmp = env;
// 		if (ft_strcmp((*strs)[i], "_"))
// 		{
// 			write(STDOUT_FILENO, "export ", 7);
// 			write(STDOUT_FILENO, (*strs)[i], ft_strlen((*strs)[i]));
// 			write(STDOUT_FILENO, "=\"", 2);
// 			while (tmp && ft_strcmp((*strs)[i], tmp->name))
// 				tmp = tmp->next;
// 			if (tmp->value)
// 				write(STDOUT_FILENO, tmp->value, ft_strlen(tmp->value));
// 			write(STDOUT_FILENO, "\"\n", 2);
// 		}
// 		env = env->next;
// 	}
// 	return (1);
// }
