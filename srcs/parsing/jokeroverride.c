/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jokeroverride.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:26:18 by bama              #+#    #+#             */
/*   Updated: 2024/08/10 14:17:34 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	there_is_joker(char *str);
void	inspect_all_files(t_data *data, t_joker joker);
char	inspect_a_file(char *file, t_joker joker);
void	joker_check_firstlast(const char *str, t_joker *joker);

char	is_sep_joker(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '*');
}

void	jokeroverride(t_token **root, t_data *data)
{
	t_joker	joker;
	t_token	*tok;

	tok = *root;
	while (tok)
	{
		if (there_is_joker((char *)tok->value))
		{
			joker_check_firstlast(tok->value, &joker);
			joker.words = ft_split_quotes(tok->value, is_sep_joker, data);
			if (!joker.words || !joker.words[0])
				joker.single = 1;
			inspect_all_files(data, joker);
		}
		tok = tok->next;
	}
}

void	inspect_all_files(t_data *data, t_joker joker)
{
	char			judge;
	struct dirent	*rd;

	data->dir = opendir(".");
	rd = readdir(data->dir);
	while (rd)
	{
		if (ft_strcmp(rd->d_name, ".") && ft_strcmp(rd->d_name, ".."))
		{
			judge = inspect_a_file(rd->d_name, joker);
			if (judge == JOKER_SINGLE)
			{
				if (ft_strncmp(rd->d_name, ".", 1))
					ft_printf("%s%sADD : %s%s\n", BOLD, ITALIC, rd->d_name, RESET);
			}
			else if (judge == JOKER_YES)
				ft_printf("%s%sADD : %s%s\n", BOLD, ITALIC, rd->d_name, RESET);
		}
		rd = readdir(data->dir);
	}
	closedir(data->dir);
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
			return (i + 1);
		i++;
	}
	return (0);
}
