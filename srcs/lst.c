/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:09:44 by bama              #+#    #+#             */
/*   Updated: 2024/07/18 17:03:55 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*last_token(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (tokens[i - 1]);
}

t_token	**ft_createtok(size_t size)
{
	t_token	**ret;

	ret = (t_token **)malloc(sizeof(t_token *) * (size + 1));
	return (ret);
}

t_token	*ft_toknew(char *value)
{
	t_token	*ret;

	ret = (t_token *)malloc(sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->type = Null;
	ret->value = value;
	return (ret);
}
