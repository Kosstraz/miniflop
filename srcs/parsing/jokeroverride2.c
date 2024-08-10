/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jokeroverride2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:26:52 by bama              #+#    #+#             */
/*   Updated: 2024/08/10 14:19:16 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_sep_joker(char c);

static void	init_t_joker(t_joker *joker)
{
	joker->at = 0;
	joker->first = 0;
	joker->last = 0;
	joker->single = 0;
}

char	inspect_a_file(char *file, t_joker joker)
{
	size_t	i;
	size_t	size;
	char	*addrs;

	if (!joker.words || !joker.words[0])
		return (JOKER_SINGLE);
	i = 0;
	size = 0;
	while (joker.words[i])
	{
		addrs = ft_strstr(&file[size], joker.words[i]);
		if (!addrs)
			return (JOKER_NO);
		if (addrs == file && !joker.words[i + 1] && !joker.first)
			return (JOKER_YES);
		if (addrs == file)
			size++;
		else
			size = addrs - file;
		i++;
	}
	if (!joker.first)
		if (ft_strncmp(file, joker.words[0], ft_strlen(joker.words[0])))
			return (JOKER_NO);
	if (!joker.last)
		if (ft_strcmp(&file[size], joker.words[i - 1]))
			return (JOKER_NO);
	return (JOKER_YES);
}

void	joker_check_firstlast(const char *str, t_joker *joker)
{
	ssize_t	i;

	i = 0;
	init_t_joker(joker);
	while (str[i] && is_sep_joker(str[i]))
	{
		if (str[i++] == '*')
		{
			joker->first = 1;
			break ;
		}
	}
	i = ft_strlen(str) - 1;
	while (str[i] && is_sep_joker(str[i]))
	{
		if (str[i--] == '*')
		{
			joker->last = 1;
			break ;
		}
	}
}