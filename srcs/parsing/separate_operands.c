/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_operands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:49:27 by bama              #+#    #+#             */
/*   Updated: 2024/07/30 00:00:45 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_new_words(char ***div, char *str, size_t *i, size_t at)
{
	size_t	ope_len;

	if ((str[at] == '|' && str[at + 1] != '|')
		|| (str[at] == '>' && str[at + 1] != '>')
		|| (str[at] == '<' && str[at + 1] != '<'))
		ope_len = 1;
	else if ((str[at] == '&' && str[at + 1] == '&')
		|| (str[at] == '|' && str[at + 1] == '|')
		|| (str[at] == '<' && str[at + 1] == '<')
		|| (str[at] == '>' && str[at + 1] == '>')
		|| (ft_isdigit(str[at]) && str[at + 1] == '>'))
		ope_len = 2;
	if (at > 0)
		(*div)[(*i)++] = ft_strdup_at(str, 0, at);
	(*div)[(*i)++] = ft_strdup_at(str, at, at + ope_len);
	if (at + ope_len < ft_strlen(str))
		(*div)[(*i)++] = ft_strdup_at(str, at + ope_len,
				ft_strlen(str));
	free(str);
}

static void	separate(char ***splitted, size_t word_at, size_t at)
{
	char	**div;
	size_t	size;
	size_t	i;
	size_t	j;

	size = 3;
	div = (char **)malloc(sizeof(char *) * (ft_strlen2(*splitted) + size + 1));
	size = ft_strlen2(*splitted);
	i = 0;
	j = 0;
	while (i < word_at)
		div[i++] = (*splitted)[j++];
	add_new_words(&div, (*splitted)[j], &i, at);
	j++;
	while (j < size)
		div[i++] = (*splitted)[j++];
	div[i] = NULL;
	free(*splitted);
	*splitted = div;
}

void	separate_operands(char ***splitted)
{
	char	quote_opened;
	size_t	i;
	size_t	j;

	i = 0;
	quote_opened = 0;
	while ((*splitted)[i])
	{
		if (ft_strlen((*splitted)[i]) > 2 || !is_operand(&(*splitted)[i][0]))
		{
			j = 0;
			while (j < ft_strlen((*splitted)[i]) && (*splitted)[i][j])
			{
				check_quote_status((*splitted)[i][j], &quote_opened);
				if (is_operand(&(*splitted)[i][j]) && !quote_opened)
					separate(splitted, i++, j);
				if (j < ft_strlen((*splitted)[i]))
					j++;
			}
		}
		i++;
	}
}
