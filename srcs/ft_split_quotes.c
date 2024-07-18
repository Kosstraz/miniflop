/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:32 by ymanchon          #+#    #+#             */
/*   Updated: 2024/07/18 16:49:46 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char c, int *quote_type);
int	parse_quotes(const char *str, int quote_type, size_t *i, size_t *old);
int	parse_squote(const char *str, size_t *i, size_t *old);
int	parse_dquote(const char *str, size_t *i, size_t *old);

static void	ft_split_free(char **tofree, size_t count)
{
	while (count > 0)
		free(tofree[count--]);
	free(tofree[0]);
	free(tofree);
}

static char	*strdup_at(const char *str, ssize_t start, ssize_t end)
{
	size_t	i;
	size_t	size;
	char	*ret;

	size = end - start;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = '\0';
	i = 0;
	while (start < end)
		ret[i++] = str[start++];
	return (ret);
}

static char	skip_sep(const char *s, size_t *i, size_t *old, char sep)
{
	int	quote_type;

	quote_type = 0;
	while (s[*i] && s[*i] == sep)
		if (s[*i] == sep)
			(*i)++;
	if (check_quotes(s[*i], &quote_type))
		return (parse_quotes(s, quote_type, i, old));
	if (!s[*i])
		return (SPLIT_ERROR);
	*old = *i;
	while (s[*i] && s[*i] != sep && !check_quotes(s[*i], &quote_type))
		if (s[*i] != sep)
			(*i)++;
	return (*i);
}

char	**ft_split_quotes(const char *s, char sep)
{
	char	**ret;
	size_t	back;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (ft_count_words(s, sep) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (skip_sep(s, &i, &back, sep) == -1)
			break ;
		if (back != i)
			ret[j] = strdup_at(s, back, i);
		if (back != i && !ret[j++])
		{
			ft_split_free(ret, j - 1);
			return (NULL);
		}
	}
	ret[j] = NULL;
	return (ret);
}
