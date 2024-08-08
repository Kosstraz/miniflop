/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:26:18 by bama              #+#    #+#             */
/*   Updated: 2024/08/08 22:08:43 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	there_is_joker(char *str);
void	recu_joker(t_data *data, char *begin, char **jokers, size_t at, char last);

char	is_sep_joker(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '*');
}

// Faire une variable first pour savoir s'il y a */
// et last pour /* ou *
// Les deux pour */*
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
			if (tok->value[0] == '*')
				last = -1;
			else if (i != 0 && tok->value[i - 1] == '*')
				last = 1;
			printf("last %d\n\n", last);
			data->tokens = tok;
			recu_joker(data, NULL, jokers, 0, last);
		}
		prev = tok;
		tok = tok->next;
	}
	if (was_null)
		*root = prev;
	data->tokens = *root;
	//exit(0);
}

// Bon*EZ

// Fonctionnel sauf quand ça commence par un '.' ... Pour une raison obscure
void	recu_joker(t_data *data, char *begin, char **jokers, size_t at, char last)
{
	char			*tmp;
	struct dirent	*rd;

	data->dirjok[at] = opendir(".");
	rd = readdir(data->dirjok[at]);
	if (jokers[at] && last != -1)
	{
		begin = strljoin(begin, jokers[at]);
	}
	while (rd)
	{
		if (last == -1 && (ft_strncmp(rd->d_name, ".", 1) || (jokers && jokers[at] && jokers[at][0] == '.')))
		{
			free(begin);
			begin = ft_strdup(rd->d_name);
			if (jokers[at])
			{
				begin = strldelete(begin, ft_strlen(begin) - ft_strlen(jokers[at]), ft_strlen(jokers[at]));
				begin = strljoin(begin, jokers[at]);
			}
			printf("beginL %s\n", begin);
		}
		//if (at != 0)
			//printf("begin[1] %s\n\n", begin);
		if (!ft_strncmp(rd->d_name, begin, ft_strlen(begin))
			&& ft_strcmp(rd->d_name, ".")
			&& ft_strcmp(rd->d_name, ".."))
		{
			printf("begin %s\n", begin);
			if (!jokers[at + 1] && last)
			{
				printf("&& LAST\n");
				tmp = ft_strdup(rd->d_name);
				printf("\e[31m %s NEW\n\e[0m", tmp);
				add_newtoken_next(tmp, &data->tokens);
				data->tokens = data->tokens->next;
			}
			else if (!jokers[at + 1] && !last)
			{
				if (!ft_strcmp(rd->d_name, begin))
				{
					printf("\e[31m %s NEW\n\e[0m", begin);
					add_newtoken_next(begin, &data->tokens);
					data->tokens = data->tokens->next;
				}
			}
			if (jokers[at] && jokers[at + 1])
			{
				printf("at %d\n", at);
				tmp = ft_strdup(rd->d_name);
				printf("dname $%s$\n", tmp);
				tmp = strldelete(tmp, ft_strlen(tmp) - ft_strlen(jokers[at + 1]), ft_strlen(jokers[at + 1]));
				printf("ldelete $%s$\n\n\n", tmp);
				recu_joker(data, tmp, jokers, at + 1, last);
			}
		}
		rd = readdir(data->dirjok[at]);
	}
	closedir(data->dirjok[at]);
}

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
