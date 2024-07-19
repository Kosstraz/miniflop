/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:29:54 by bama              #+#    #+#             */
/*   Updated: 2024/07/18 23:21:38 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_quote_type(const char c, int *quote_stat, int *quotes_to_r)
{
	if (*quote_stat == 1 && c == '\'')
	{
		*quotes_to_r += 1;
		*quote_stat = 0;
	}
	else if (*quote_stat == 2 && c == '"')
	{
		*quotes_to_r += 1;
		*quote_stat = 0;
	}
}

static int	count_useless_quotes(const char *line)
{
	int	quote_status;
	int	quotes_to_remove;
	int	i;

	i = 0;
	quote_status = 0;
	quotes_to_remove = 0;
	while (line[i])
	{
		if (quote_status && line[i] == ' ')
			quote_status = 0;
		if (!quote_status && line[i] == '\'')
			quote_status = 1;
		else if (!quote_status && line[i] == '"')
			quote_status = 2;
		check_quote_type(line[i++], &quote_status, &quotes_to_remove);
	}
	return (quotes_to_remove);
}

char	*remove_useless_quotes(const char *line)
{
	char	*ret;
	int		size;
	int		quote_status;
	int		quotes_to_remove;
	int		i;

	i = 0;
	quote_status = 0;
	quotes_to_remove = count_useless_quotes(line);
	size = ft_strlen(line) - quotes_to_remove;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	
}
