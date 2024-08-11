/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jokeroverride.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:26:18 by bama              #+#    #+#             */
/*   Updated: 2024/08/11 20:51:32 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	there_is_joker(char *str);
void	inspect_all_files(t_data *data, t_token **prev, t_joker joker);
char	inspect_a_file(char *file, t_joker joker);
void	joker_check_firstlast(const char *str, t_joker *joker);
char	is_sep_joker(char c);
void	add_joker_to_token(char *file, t_token **current, t_token **newtok);

void	jokeroverride(t_token **root, t_data *data)
{
	t_joker	joker;
	t_token	*tok;
	t_token	*joks;

	joks = NULL;
	tok = *root;
	while (tok)
	{
		if (there_is_joker((char *)tok->value))
		{
			joker_check_firstlast(tok->value, &joker);
			joker.words = ft_split_quotes(tok->value, is_sep_joker, data);
			data->dir = opendir(".");
			inspect_all_files(data, &joks, joker);
			if (!joks)
				ft_printf(JOKER_ERROR, BOLD, CURLY, LINE_RED,
						tok->value, RESET, BOLD, RESET);
			insert_token(&tok, joks);
			delete_token(root, &tok);
			dfree((void **)joker.words);
		}
		if (!tok)
			return ;
		tok = tok->next;
	}
}

void	inspect_all_files(t_data *data, t_token **newtok, t_joker joker)
{
	char			judge;
	t_token			*tmp;
	struct dirent	*rd;

	tmp = *newtok;
	rd = readdir(data->dir);
	while (rd)
	{
		if (ft_strcmp(rd->d_name, ".") && ft_strcmp(rd->d_name, ".."))
		{
			judge = inspect_a_file(rd->d_name, joker);
			if (judge == JOKER_SINGLE)
			{
				if (ft_strncmp(rd->d_name, ".", 1))
					add_joker_to_token(rd->d_name, &tmp, newtok);
			}
			else if (judge == JOKER_YES)
				add_joker_to_token(rd->d_name, &tmp, newtok);
		}
		rd = readdir(data->dir);
	}
	closedir(data->dir);
	data->dir = NULL;
}

void	add_joker_to_token(char *file, t_token **current, t_token **newtok)
{
	if (!(*current))
	{
		*current = new_token(ft_strdup(file));
		*newtok = *current;
	}
	else
	{
		(*current)->next = new_token(ft_strdup(file));
		*current = (*current)->next;
	}
}