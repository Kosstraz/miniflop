/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jokeroverride2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:26:52 by bama              #+#    #+#             */
/*   Updated: 2024/08/10 03:13:48 by bama             ###   ########.fr       */
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
