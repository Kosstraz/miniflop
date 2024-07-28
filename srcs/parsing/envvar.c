/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:43:15 by bama              #+#    #+#             */
/*   Updated: 2024/07/28 12:00:18 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*modify_word(const char *s, const char *varname, char *env,
			size_t at)
{
	char	*ret;
	char	*dup;

	ret = NULL;
	dup = ft_strdup_at(s, 0, at);
	ret = ft_strssjoin(ret, dup);
	free(dup);
	if (env)
	{
		dup = ft_strdup(env);
		ret = ft_strssjoin(ret, dup);
	}
	if (ft_strlen(varname) != ft_strlen(s) - 1)
	{
		dup = ft_strdup_at(s, at + 1 + ft_strlen(varname), ft_strlen(s));
		ret = ft_strssjoin(ret, dup);
	}
	return (ret);
}

static char	*add_envvar(char *s, size_t at, size_t *varlen)
{
	char	*ret;
	char	*env;
	char	varname[ARG_MAX + 1];
	size_t	varname_len;
	size_t	i;

	i = 0;
	if (is_sep(s[at + 1]) || s[at + 1] == '"')
		return (*varlen = 1, s);
	while (s[at + i] && s[at + i] != ' '
		&& s[at + i] != '\'' && s[at + i] != '"')
	{
		i++;
		if (s[at + i] == '$')
			break ;
	}
	varname_len = i;
	ft_strlcpy(&varname[1], &s[at + 1], varname_len);
	env = getenv(&varname[1]);
	*varlen = ft_strlen(env);
	ret = modify_word(s, &varname[1], env, at);
	free(s);
	return (ret);
}

void	place_envvars(char ***splitted)
{
	char	**tmp;
	char	quote_status;
	size_t	varlen;
	size_t	i;
	size_t	j;

	tmp = *splitted;
	quote_status = 0;
	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			check_quote_status(tmp[i][j], &quote_status);
			if (tmp[i][j] == '$' && quote_status != 1)
			{ 
				tmp[i] = add_envvar(tmp[i], j, &varlen);
				j += varlen - 1;
			}
			j++;
		}
		i++;
	}
	*splitted = tmp;
}
