/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jokeroverride2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:26:52 by bama              #+#    #+#             */
/*   Updated: 2024/11/07 14:40:10 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_sep_joker(char c);

static void	init_t_joker(t_joker *joker)
{
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
	{
		if (ft_strncmp(file, joker.words[0], ft_strlen(joker.words[0])))
			return (JOKER_NO);
	}
	else if (joker.first && !ft_strncmp(file, ".", 1) && ft_strcmp(file, "."))
	{
		//write(1, file, ft_strlen(file)); write(1, "\n", 1);
		//write(1, &file[size], ft_strlen(&file[size])); write(1, "\n", 1);
		//write(1, joker.words[i - 1], ft_strlen(joker.words[i - 1])); write(1, "\n", 1);
		//write(1, "ezezez", 6);
		return (JOKER_NO);
	}
	if (!joker.last && ft_strcmp(&file[size], joker.words[i - 1]))
		return (JOKER_NO);
	//write(1, file, ft_strlen(file)); write(1, "\n", 1);
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

BOOL	there_is_joker(char *str)
{
	size_t	i;
	BOOL	quote_status;

	if (!str)
		return (0);
	i = 0;
	quote_status = 0;
	while (str[i])
	{
		check_quote_status(str[i], &quote_status);
		if (str[i] == '*' && !quote_status)
			return (i + 1);
		i++;
	}
	return (0);
}

BOOL	is_sep_joker(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '*');
}
