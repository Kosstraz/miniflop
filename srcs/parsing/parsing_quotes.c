/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:29:54 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 16:42:37 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  commandword_len
static size_t	cwlen(char *word)
{
	int		passed;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	passed = 0;
	while (word[i])
	{
		if ((passed == 1 && word[i] == '\'') || (passed == 2 && word[i] == '"'))
			passed = 0;
		else if (word[i] == '\'' && !passed)
			passed = 1;
		else if (word[i] == '"' && !passed)
			passed = 2;
		else if ((word[i] != '\'' && word[i] != '"')
			|| (passed && (word[i] == '\'' || word[i] == '"')))
			len++;
		i++;
	}
	return (len);
}

size_t	ft_strlcpy_quotes(char *dst, const char *src, size_t size)
{
	int		passed;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	passed = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && (i <= size))
	{
		if ((passed == 1 && src[i] == '\'') || (passed == 2 && src[i] == '"'))
			passed = 0;
		else if (src[i] == '\'' && !passed)
			passed = 1;
		else if (src[i] == '"' && !passed)
			passed = 2;
		else if ((src[i] != '\'' && src[i] != '"')
			|| (passed && (src[i] == '\'' || src[i] == '"')))
			dst[j++] = src[i];
		i++;
	}
	dst[j] = '\0';
	return (ft_strlen(src));
}

void	check_validity(char **src, char *word, size_t *src_idx, int size)
{
	if (size > 0)
	{
		ft_strlcpy_quotes(src[(*src_idx)++], word, size + 1);
		free(word);
	}
	else
		free(src[*src_idx]);
}

char	**remove_useless_quotes(char **splitted)
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
		size = cwlen(splitted[i]);
		ret[j] = (char *)malloc(sizeof(char) * (size + 1));
		if (!ret[j])
			return (NULL);
		check_validity(ret, splitted[i], &j, size);
		i++;
	}
	while (j <= size2)
		ret[j++] = NULL;
	free(splitted);
	return (ret);
}
