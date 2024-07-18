/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:08:41 by bama              #+#    #+#             */
/*   Updated: 2024/07/18 17:04:19 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cherche le type de token auquel correspond le mot splitté
static void	check_e_type(t_token **tokens, const char *word, int i)
{
	enum e_type	type;

	type = Null;
	if (i == 0 || tokens[i - 1]->type == Pipe
		|| tokens[i - 1]->type == And || tokens[i - 1]->type == Or)
		type = Command;
	else if (ft_strlen(word) == 1)
	{
		if (word[0] == '|')
			type = Pipe;
	}
	else if (ft_strlen(word) == 2)
	{
		if (word[0] == '&' && word[1] == '&')
			type = And;
		else if (word[0] == '|' && word[1] == '|')
			type = Or;
	}
	if (i != 0
		&& ((tokens[i - 1]->type == Command || tokens[i - 1]->type == Argument)
			&& type == Null))
		type = Argument;
	tokens[i]->type = type;
}

static t_token	**parse_commandline(const char *line)
{
	char	**splitted;
	t_token	**tokens;
	t_token	**root;
	int		i;

	i = 0;
	splitted = ft_split_quotes(line, ' ');
	root = ft_createtok(ft_strlen2((const char **)splitted));
	tokens = root;
	while (splitted[i])
	{
		tokens[i] = ft_toknew(splitted[i]);
		check_e_type(tokens, splitted[i], i);
		i++;
	}
	tokens[i] = NULL;
	show_token((const t_token **)tokens);
	return (root);
}

static const char	*maybe_continued(void)
{
	if (errcode == 0)
		return (NULL);
	else if (errcode = SQUOTE_MISSING)
	{
		
	}
	else if (errcode = DQUOTE_MISSING)
	{
		
	}
}

void	take_commandline(const char *line)
{
	t_token		**tokens;
	const char	*continued;

	tokens = parse_commandline(line);
	continued = maybe_continued();
	if (continued)
	{
		//tokens[] = ft_toknew(splitted[i]);
		check_e_type(tokens, splitted[i], i);
	}
}
