/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:35:18 by ymanchon          #+#    #+#             */
/*   Updated: 2024/07/19 16:33:16 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_statictab(size_t tab1[2], size_t tab2[2])
{
	tab1[0] = -1;
	tab1[1] = -1;
	tab2[0] = -1;
	tab2[1] = -1;
}

static void	find_closing_quote(const char *str, const char sep, size_t *i,
			size_t quotetab[2])
{
	size_t	tmp;
	char	c;

	if (quotetab[0] == 1)
		c = '\'';
	else if (quotetab[0] == 2)
		c = '"';
	tmp = *i;
	if (*i != 0 && str[*i - 1] != sep)
	{
		while (str[*i] && str[*i] != sep)
		{
			
			(*i)++;
		}
	}
	while (str[*i])
	{
		
		(*i)++;
	}
	quotetab[0] = -1;
	quotetab[1] = -1;
}

/*
	echo e"cho" """"'""'""'t'f'' | BONJOUR
	echo w"Yo tout le monde"
*/

static size_t	count_tokens(const char *str, const char sep)
{
	size_t	dquotes[2];
	size_t	squotes[2];
	size_t	tokensc;
	size_t	i;
	char	c;

	init_statictab(squotes, dquotes);
	tokensc = 0;
	i = 0;
	while (str[i])
	{
		c = str[i];
		if (i == 0 && c != sep)
			tokensc++;
		else if (i != 0 && c != sep && str[i - 1] == sep)
			tokensc++;
		if (c == '"' && squotes[0] == -1)
		{
			dquotes[0] = 2;
			find_closing_quote(str, sep, &i, dquotes);
		}
		else if (c == '\'' && dquotes[0] == -1)
		{
			squotes[0] = 1;
			find_closing_quote(str, sep, &i, squotes);
		}
		i++;
	}
	return (tokensc);
}

char	**minisplit(const char *str, const char sep)
{
	char	**splitted;
	size_t	tokensc;
	size_t	i;

	tokensc = count_tokens(str, sep);
	splitted = (char **)malloc(sizeof(char *) * (tokensc + 1));
	if (!splitted)
		return (NULL);
	while (i < tokensc)
	{
		i++;
	}
	splitted[tokensc] = NULL;
	return (splitted);
}
