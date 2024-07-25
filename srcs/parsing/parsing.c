/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:08:41 by bama              #+#    #+#             */
/*   Updated: 2024/07/25 11:45:51 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_some_parsing(char ***splitted, const char *line)
{	
	*splitted = ft_split_quotes(line, ' ');
	place_envvars(splitted);
	separate_operands(splitted);
	place_wildcards(splitted);
	*splitted = remove_useless_quotes(*splitted);
}

// Bon"jour mec MOUAH"AHAHH "why are you raging ??" "" A"urevoir "

static t_token	*parse_commandline(const char *line)
{
	char	**splitted;
	t_token	*token;
	t_token	*root;
	int		i;

	do_some_parsing(&splitted, line);
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
	free(splitted);
	review_tokenid(&root);
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
