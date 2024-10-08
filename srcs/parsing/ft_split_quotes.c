/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:10:32 by ymanchon          #+#    #+#             */
/*   Updated: 2024/08/10 14:06:48 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_quotes(char c, int *quote_type, t_data *data);
int		parse_quotes(const char *str, int quote_type, size_t *i,
			t_data *data);
size_t	ft_count_words_quotes(const char *s, t_data *data);

static void	ft_split_free(char **tofree, size_t count)
{
	while (count > 0)
		free(tofree[count--]);
	free(tofree[0]);
	free(tofree);
}

static char	skip_sep(const char *s, size_t *i, size_t *old, t_data *data)
{
	int		quote_type;
	char	(*_is_sep_)(char);

	_is_sep_ = data->_is_sep_;
	quote_type = 0;
	while (s[*i] && _is_sep_(s[*i]))
		(*i)++;
	if (!s[*i])
		return (SPLIT_ERROR);
	*old = *i;
	while (s[*i] && !_is_sep_(s[*i]) && !check_quotes(s[*i], &quote_type, data))
		(*i)++;
	if (quote_type)
	{
		(*i)++;
		parse_quotes(s, quote_type, i, data);
		if (s[*i])
			(*i)++;
	}
	return (*i);
}
/*
		Bon"jour mec MOUAH"AHAHH "why are you raging ??" "" A"urevoir "
*/

char	**ft_split_quotes(const char *s, char (*_is_sep_)(char c), t_data *data)
{
	char	**ret;
	size_t	back;
	size_t	i;
	size_t	j;

	data->_is_sep_ = _is_sep_;
	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (ft_count_words_quotes(s, data) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (skip_sep(s, &i, &back, data) <= -1)
			break ;
		ret[j] = ft_strdup_at(s, back, i);
		if (!ret[j++])
		{
			ft_split_free(ret, j - 1);
			return (NULL);
		}
	}
	ret[j] = NULL;
	return (ret);
}
