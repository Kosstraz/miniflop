/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:08:41 by bama              #+#    #+#             */
/*   Updated: 2024/07/28 18:13:05 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_some_parsing(char ***splitted, const char *line, t_data *data)
{
	*splitted = ft_split_quotes(line, data);
	place_envvars(splitted);
	separate_operands(splitted);
	apply_wildcards(splitted);
	*splitted = remove_useless_quotes(*splitted);
}

// Bon"jour mec MOUAH"AHAHH "why are you raging ??" "" A"urevoir "

static t_token	*parse_commandline(const char *line, t_data *data)
{
	char	**splitted;
	t_token	*token;
	t_token	*root;
	int		i;

	do_some_parsing(&splitted, line, data);
	token = new_token(splitted[0]);
	token->type = Command;
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
	return (root);
}

static char	*maybe_prompt(t_data *data, t_token **tokens)
{
	char	*buffer;
	char	**splitted;
	char	*gnl;

	if (data->_errcode < 0)
	{
		printf("%d\n", data->_errcode);
		buffer = NULL;
		gnl = NULL;
		new_missing_prompt((char)data->_errcode);
		gnl = get_next_line(STDIN_FILENO);
		while (gnl)
		{
			do_some_parsing(&splitted, gnl, data);
			show_token(*tokens);
			new_missing_prompt((char)data->_errcode);
			if (ft_strstr(gnl, return_missing_chars(data->_errcode)))
			{
				data->_errcode = 0;
				break ;
			}
			free(gnl);
			gnl = get_next_line(STDIN_FILENO);
		}
	}
	data->_errcode = 0;
}

void	take_commandline(const char *line, t_data *data)
{
	t_token	*tokens;
 
	tokens = parse_commandline(line, data);
	data->tokens = tokens;
	show_token(tokens);
 	while (is_missing_septoktype(data->_errcode))
		maybe_prompt(data, &tokens);
}
