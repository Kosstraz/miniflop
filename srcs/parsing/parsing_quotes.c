/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:29:54 by bama              #+#    #+#             */
/*   Updated: 2024/08/04 17:10:44 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  commandword_len
static size_t	cwlen(char *word, t_data *data)
{
	char	quote_status;
	size_t	len;
	size_t	i;

	(void)data;
	i = 0;
	len = 0;
	quote_status = 0;
	while (word[i])
	{
		check_quote_status(word[i], &quote_status);
		if ((word[i] != '\'' && word[i] != '"')
			|| ((quote_status == 1 && word[i] != '\'')
				|| (quote_status == 2 && word[i] != '"')))
			len++;
		i++;
	}
	return (len);
}

size_t	ft_strlcpy_quotes(char *dst, const char *src, size_t size, t_data *data)
{
	char	quote_status;
	size_t	i;
	size_t	l;
	size_t	j;

	(void)data;
	i = 0;
	l = 0;
	j = 0;
	quote_status = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && l < size)
	{
		check_quote_status(src[i], &quote_status);
		if ((src[i] != '\'' && src[i] != '"')
			|| ((quote_status == 1 && src[i] != '\'')
				|| (quote_status == 2 && src[i] != '"')))
		{
			l++;
			dst[j++] = src[i];
		}
		i++;
	}
	dst[j] = '\0';
	return (ft_strlen(src));
}

void	check_validity(char **src, char *word, size_t *src_idx, t_data *data)
{
	size_t	size;

	size = cwlen(word, data);
	if (size > 0)
	{
		ft_strlcpy_quotes(src[(*src_idx)++], word, size, data);
		free(word);
	}
	else
		free(src[*src_idx]);
}

char	**remove_useless_quotes(char **splitted, t_data *data)
{
	char	**ret;
	size_t	size2;
	size_t	size;
	size_t	i;
	size_t	j;

	size2 = ft_strlen2(splitted);
	ret = (char **)malloc(sizeof(char *) * (size2 + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (splitted[i])
	{
		size = cwlen(splitted[i], data);
		ret[j] = (char *)malloc(sizeof(char) * (size + 1));
		if (!ret[j])
			return (NULL);
		check_validity(ret, splitted[i], &j, data);
		i++;
	}
	while (j <= size2)
		ret[j++] = NULL;
	free(splitted);
	return (ret);
}
