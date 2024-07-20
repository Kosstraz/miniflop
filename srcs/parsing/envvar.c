/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:43:15 by bama              #+#    #+#             */
/*   Updated: 2024/07/20 13:52:57 by bama             ###   ########.fr       */
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
	char	varname[ARG_MAX];
	size_t	varname_len;
	size_t	i;

	i = 0;
	while (s[at + i] && s[at + i] != ' '
		&& s[at + i] != '\'' && s[at + i] != '"')
	{
		i++;
		if (s[at + i] == '$')
			break ;
	}
	varname_len = i;
	ft_strlcpy(varname, &s[at + 1], varname_len);
	env = getenv(varname);
	*varlen = ft_strlen(env);
	ret = modify_word(s, varname, env, at);
	free(s);
	return (ret);
}

void	place_envvars(char ***splitted)
{
	char	**tmp;
	size_t	varlen;
	size_t	i;
	size_t	j;

	tmp = *splitted;
	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			if (tmp[i][j] == '$')
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
