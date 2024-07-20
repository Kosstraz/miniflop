/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_operands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:49:27 by bama              #+#    #+#             */
/*   Updated: 2024/07/20 17:42:30 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*separate(char **splitted, size_t word_at, size_t at)
{
	
}

void	separate_operands(char ***splitted)
{
	char	quote_opened;
	char	**tmp;
	size_t	i;
	size_t	j;

	i = 0;
	tmp = *splitted;
	quote_opened = 0;
	while (splitted[i])
	{
		if (ft_strlen(splitted[i]) > 1)
		{
			j = 0;
			while (splitted[i][j])
			{
				check_quote_status(splitted[i][j], &quote_opened);
				if (is_operand(&splitted[i][j]) && !quote_opened)
					splitted[i] = separate(splitted, i, j);
				j++;
			}
		}
		i++;
	}
	*splitted = tmp;
}
