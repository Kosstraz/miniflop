/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:26:18 by bama              #+#    #+#             */
/*   Updated: 2024/08/08 14:26:14 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	there_is_joker(char *str);
void	recu_joker(t_data *data, char *begin, char **jokers, size_t at, char last);

char	is_sep_joker(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '*');
}

void	jokeroverride(t_token **root, t_data *data)
{
	t_token	*tok;
	t_token	*prev;
	char	**jokers;
	char	was_null;

	prev = NULL;
	tok = *root;
	was_null = 0;
	tokenise_joker(root);
	while (tok)
	{
		if (tok->joker)
		{
			if (!prev)
				was_null = 1;
			jokers = ft_split_quotes(tok->value, is_sep_joker, data);
			int last = 0;
			int i;
			for (i = 0 ; tok->value[i] ; i++)
				;
			if (tok->value[i - 1] == '*')
				last = 1;
			recu_joker(data, NULL, jokers, 0, last);
		}
		prev = tok;
		tok = tok->next;
	}
	if (was_null)
		*root = prev;
	//exit(0);
}

// Bon*EZ

// Bon --> Bonjour
// BonjourEZ
void	recu_joker(t_data *data, char *begin, char **jokers, size_t at, char last)
{
	char			*tmp;
	struct dirent	*rd;

	if (!jokers[at])
		return ;
	data->dirjok[at] = opendir(".");
	rd = readdir(data->dirjok[at]);
	begin = ft_strsjoin(begin, jokers[at]);
	while (rd)
	{
		if (!ft_strncmp(rd->d_name, begin, ft_strlen(begin)))
		{
			if (!jokers[at + 1] && last)
			{
				tmp = ft_strdup(rd->d_name);
				printf("\e[31m %s NEW\n\e[0m", tmp);
			}
			else if (!jokers[at + 1] && !last)
				if (!ft_strcmp(rd->d_name, begin))
					printf("\e[31m %s NEW\n\e[0m", begin);
			if (jokers[at + 1])
			{
				tmp = ft_strdup(rd->d_name);
				tmp = strldelete(tmp, ft_strlen(tmp) - ft_strlen(jokers[at + 1]), ft_strlen(jokers[at + 1]));
				recu_joker(data, tmp, jokers, at + 1, last);
			}
		}
		rd = readdir(data->dirjok[at]);
	}
	closedir(data->dirjok[at]);
}

// Remplacer le '*' à 'at'
// Et potentiellement créer une branche dans (t_token *)
/*void	recu_joker(char *word, t_token **prev, DIR *dir, size_t at)
{
	char			*ret;
	char			*tmp;
	size_t			size;
	size_t			i;
	struct dirent	*rd;

	if (!dir)
		dir = opendir(".");
	if (take_dir(word) && !there_is_joker(word))
	{
		if (dir)
			closedir(dir);
		dir = opendir(take_dir(word));
		word = take_absocmd(word);
	}
	if (!dir)
		return ;
	size = cwlen_joker(&word[at]);
	//faire un sizeafter = cwindex_afterjoker(&word[at]) qui prend la position après tous les '*'
	// passé s'il y en a plusieurs simultanés
	printf("size %d\n", size);
	tmp = (char *)malloc(sizeof(char) * (size + 1));
	remquotes_joker(&tmp, &word[at]);
	ret = ft_strdup_at(word, 0, at);
	ret = ft_strssjoin(ret, tmp);
	//ret = strldelete(ret, there_is_joker(&ret[at]), 1);
	printf("ret $%s$\nat %d\n", ret, at);
	rd = readdir(dir);
	while (rd)
	{
		if (ft_strncmp(rd->d_name, ".", 1) && !ft_strncmp(rd->d_name, ret, ft_strlen(ret)))
		{
			//free(ret);
			tmp = ft_strdup(rd->d_name);
			write(1, "tmp $", 6);
			write(1, tmp, ft_strlen(tmp));
			write(1, "$\n", 2);
			if (there_is_joker(&ret[size]))
				recu_joker(ret, prev, dir, size);
			if (!word[size + 1] || !ft_strncmp_rev(tmp, &word[size + 1], ft_strlen(&word[size + 1])))
			{
				write(1, "\e[31mnew\e[0m\n", 14);
				add_newtoken_next(tmp, prev);
			}
		}
		rd = readdir(dir);
	}
	return ;
}*/

void	tokenise_joker(t_token **root)
{
	t_token	*tok;
	size_t	i;
	char	quote_status;

	tok = *root;
	quote_status = 0;
	while (tok)
	{
		i = 0;
		while (tok->value[i])
		{
			check_quote_status(tok->value[i], &quote_status);
			if (tok->value[i] == '*' && !quote_status)
			{
				tok->joker = TRUE;
				break ;
			}
			i++;
		}
		tok = tok->next;
	}
}

char	there_is_joker(char *str)
{
	size_t	i;
	char	quote_status;

	if (!str)
		return (0);
	i = 0;
	quote_status = 0;
	while (str[i])
	{
		check_quote_status(str[i], &quote_status);
		if (str[i] == '*' && !quote_status)
			return (i);
		i++;
	}
	return (0);
}
