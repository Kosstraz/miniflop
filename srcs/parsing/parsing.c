/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:08:41 by bama              #+#    #+#             */
/*   Updated: 2024/07/20 19:45:21 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Cherche le type de token auquel correspond le mot splitté
static void	check_e_type(t_token **second, const char *word, int i)
{
	enum e_type	type;

	type = Null;
	if (i == 0 || (*second)->type == Pipe
		|| (*second)->type == And || (*second)->type == Or)
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
		&& (((*second)->type == Command || (*second)->type == Argument)
			&& type == Null))
		type = Argument;
	(*second)->next->type = type;
}

// Bon"jour mec MOUAH"AHAHH "why are you raging ??" "" A"urevoir "

static t_token	*parse_commandline(const char *line)
{
	char	**splitted;
	t_token	*token;
	t_token	*root;
	int		i;

	splitted = ft_split_quotes(line, ' ');
	place_envvars(&splitted);
	separate_operands(&splitted);
	splitted = remove_useless_quotes(splitted);
	token = new_token(splitted[0]);
	token->type = Command;		// Rendre automatique (et surtt correcte) la tokenisation du premier token
	root = token;
	i = 1;
	while (splitted[i])
	{
		token->next = new_token(splitted[i]);
		check_e_type(&token, splitted[i], i);
		token = token->next;
		i++;
	}
	token = NULL;
	free(splitted);
	show_token(root);
	return (root);
}

void	take_commandline(const char *line, t_data *datas)
{
	t_token	*tokens;
	//char	*continued;

	tokens = parse_commandline(line);
	datas->tokens = tokens;
	//printf("errcode = %d\n", errcode);
	//continued = maybe_continued();
}
