/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jokeroverride.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:26:18 by bama              #+#    #+#             */
/*   Updated: 2024/08/13 14:13:13 by bama             ###   ########.fr       */
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
	char			judge;
	t_token			*tmp;
	struct dirent	*rd;

	joker_check_firstlast(joker.dirs[joker.at], &joker);
	joker.words = ft_split_quotes(joker.dirs[joker.at], is_sep_joker, data);
	if (joker.at == 0 && !dir)
		joker.dir = ft_strdup(".");
	else
	{
		if (joker.at == 1)
		{
			free(joker.dir);
			joker.dir = NULL;
		}
		joker.dir = strljoin(joker.dir, dir);
		joker.dir = strljoin(joker.dir, "/");
	}
	data->dirjok[joker.at] = opendir(joker.dir);
	if (!data->dirjok[joker.at])
		return ;
	tmp = *newtok;
	rd = readdir(data->dirjok[joker.at]);
	while (rd)
	{
		if (ft_strcmp(rd->d_name, ".") && ft_strcmp(rd->d_name, "..")
			&& ((!ft_strncmp(rd->d_name, ".", 1) && !ft_strncmp(joker.words[0], ".", 1))
				|| (ft_strncmp(rd->d_name, ".", 1) && ft_strncmp(joker.words[0], ".", 1))))
		{
			judge = inspect_a_file(rd->d_name, joker);
			if (judge == JOKER_SINGLE)
			{
				if (ft_strncmp(rd->d_name, ".", 1) && joker.at == joker.dirslen - 1)
				{
					if (joker.at != 0)
						ft_printf("%sADD : %s%s\n", BOLD, ft_strjoin(joker.dir, rd->d_name), RESET);//add_joker_to_token(rd->d_name, &tmp, newtok);
					else
						ft_printf("%sADD : %s%s\n", BOLD, rd->d_name, RESET);//add_joker_to_token(rd->d_name, &tmp, newtok);
				}
				else if (joker.at < joker.dirslen - 1)
				{
					joker.at++;
					joker.save = ft_strdup(joker.dir);
					printf("dname %s\n", rd->d_name);
					inspect_all_files(data, ft_strdup(rd->d_name), newtok, joker);
					joker.dir = joker.save;
					joker.at--;
				}
			}
			else if (judge == JOKER_YES)
			{
				if (joker.at == joker.dirslen - 1)
				{
					if (joker.at != 0)
						ft_printf("%sADD : %s%s\n", BOLD, ft_strjoin(joker.dir, rd->d_name), RESET);//add_joker_to_token(rd->d_name, &tmp, newtok);
					else
						ft_printf("%sADD : %s%s\n", BOLD, rd->d_name, RESET);//add_joker_to_token(rd->d_name, &tmp, newtok);
				}
				else if (joker.at < joker.dirslen - 1)
				{
					joker.at++;
					joker.save = ft_strdup(joker.dir);
					inspect_all_files(data, ft_strdup(rd->d_name), newtok, joker);
					joker.dir = joker.save;
					joker.at--;
				}
			}
		}
		rd = readdir(data->dirjok[joker.at]);
	}
	free(dir);
	closedir(data->dirjok[joker.at]);
	data->dirjok[joker.at] = NULL;
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