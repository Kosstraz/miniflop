/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jokeroverride.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:26:18 by bama              #+#    #+#             */
/*   Updated: 2024/08/13 20:15:17 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	there_is_joker(char *str);
void	inspect_all_files(t_data *data, char *dir, t_token **prev, t_joker joker);
char	inspect_a_file(char *file, t_joker joker);
void	joker_check_firstlast(const char *str, t_joker *joker);
char	is_sep_joker(char c);
void	add_joker_to_token(char *file, t_token **current, t_token **newtok);
void	prepare_inspection(t_data *data, t_token **currtok, t_token **newtok);
DIR		*joker_opendir(char	*dir, t_joker *joker);
void	joker_launch_recursion(t_data *data, char *dir,
		t_token **newtok, t_joker *joker);
void	exit_joker(t_joker joker);
void	where_place_joker(char *d_name, t_token **current, t_token **newtok,
		t_joker joker);
void	is_joker_valid(t_data *data, t_token **newtok, char *d_name, t_joker *joker);

void	jokeroverride(t_token **root, t_data *data)
{
	t_token	*tok;
	t_token *joks;

	joks = NULL;
	tok = *root;
	while (tok)
	{
		if (there_is_joker((char *)tok->value))
		{
			prepare_inspection(data, &tok, &joks);
			insert_token(&tok, joks);
			delete_token(root, &tok);
		}
		if (!tok)
			return ;
		tok = tok->next;
	}
}

void	prepare_inspection(t_data *data, t_token **currtok, t_token **newtok)
{
	t_joker	joker;

	joker.at = 0;
	if ((*currtok)->value[0] == '/')
		joker.absolute = 1;
	else
		joker.absolute = 0;
	joker.dirs = ft_split((*currtok)->value, '/');
	joker.dirslen = ft_strlen2(joker.dirs);
	inspect_all_files(data, NULL, newtok, joker);
	if (!*newtok)
		ft_printf(JOKER_ERROR, BOLD, CURLY, LINE_RED,
				(*currtok)->value, RESET, BOLD, RESET);
	dfree((void **)joker.dirs);
}

void	inspect_all_files(t_data *data, char *dir, t_token **newtok, t_joker joker)
{
	struct dirent	*rd;

	joker_check_firstlast(joker.dirs[joker.at], &joker);
	joker.words = ft_split_quotes(joker.dirs[joker.at], is_sep_joker, data);
	joker.dijok[joker.at] = joker_opendir(dir, &joker);
	if (!joker.dijok[joker.at])
		return (exit_joker(joker));
	joker.lastfromrecu = *newtok;
	rd = readdir(joker.dijok[joker.at]);
	while (rd)
	{
		if (ft_strcmp(rd->d_name, ".") && ft_strcmp(rd->d_name, "..")
			&& ((!ft_strncmp(rd->d_name, ".", 1) && !ft_strncmp(joker.words[0], ".", 1))
				|| (ft_strncmp(rd->d_name, ".", 1) && ft_strncmp(joker.words[0], ".", 1))))
		{
			joker.judge = inspect_a_file(rd->d_name, joker);
			is_joker_valid(data, newtok, rd->d_name, &joker);
		}
		rd = readdir(joker.dijok[joker.at]);
	}
	free(dir);
	closedir(joker.dijok[joker.at]);
	joker.dijok[joker.at] = NULL;
	dfree((void **)joker.words);
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

void	exit_joker(t_joker joker)
{
	free(joker.words);
	free(joker.dir);
}