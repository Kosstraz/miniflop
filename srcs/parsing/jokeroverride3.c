/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jokeroverride3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:48:58 by bama              #+#    #+#             */
/*   Updated: 2024/08/13 20:16:27 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_joker_to_token(char *file, t_token **current, t_token **newtok);

DIR	*joker_opendir(char	*dir, t_joker *joker)
{
	if (joker->at == 0 && !dir && joker->absolute)
		joker->dir = ft_strdup("/");
	else if (joker->at == 0 && !dir)
		joker->dir = ft_strdup(".");
	else
	{
		if (joker->at == 1 && !joker->absolute)
		{
			free(joker->dir);
			joker->dir = NULL;
		}
		joker->dir = strljoin(joker->dir, dir);
		joker->dir = strljoin(joker->dir, "/");
	}
	return (opendir(joker->dir));
}

void	joker_launch_recursion(t_data *data, char *dir,
		t_token **newtok, t_joker *joker)
{
	joker->at++;
	joker->save = ft_strdup(joker->dir);
	inspect_all_files(data, dir, newtok, *joker);
	joker->dir = joker->save;
	joker->at--;
}

void	where_place_joker(char *d_name, t_token **current, t_token **newtok, t_joker joker)
{
	if (joker.at != 0)
		add_joker_to_token(ft_strjoin(joker.dir, d_name), current, newtok);
	else
		add_joker_to_token(ft_strdup(d_name), current, newtok);
	/*if (joker.at != 0)
		ft_printf("%sADD : %s%s\n", BOLD, ft_strjoin(joker.dir, d_name), RESET);
	else
		ft_printf("%sADD : %s%s\n", BOLD, ft_strdup(d_name), RESET);*/
}

void	is_joker_valid(t_data *data, t_token **newtok, char *d_name, t_joker *joker)
{
	if (joker->judge == JOKER_SINGLE)
	{
		if (ft_strncmp(d_name, ".", 1) && joker->at == joker->dirslen - 1)
			where_place_joker(d_name, &joker->lastfromrecu, newtok, *joker);
		else if (joker->at < joker->dirslen - 1)
			joker_launch_recursion(data, ft_strdup(d_name), newtok, joker);
	}
	else if (joker->judge == JOKER_YES)
	{
		if (joker->at == joker->dirslen - 1)
			where_place_joker(d_name, &joker->lastfromrecu, newtok, *joker);
		else if (joker->at < joker->dirslen - 1)
			joker_launch_recursion(data, ft_strdup(d_name), newtok, joker);
	}
}
