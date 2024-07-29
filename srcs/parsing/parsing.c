/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:08:41 by bama              #+#    #+#             */
/*   Updated: 2024/07/29 15:42:14 by bama             ###   ########.fr       */
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

static void	unfinished_prompt()
{
	
}

static void	maybe_prompt(t_data *data, t_token **tokens)
{
	char	**splitted;
	char	*gnl;

	if (data->_errcode < 0)
	{
		printf("%d\n", data->_errcode);
		gnl = NULL;
		new_missing_prompt((char)data->_errcode);
		gnl = get_next_line(STDIN_FILENO);
		while (!_sig)
		{
			if (gnl)
			{
				do_some_parsing(&splitted, gnl, data);
				if (splitted && !splitted[0])
					splitted[0] = ft_strdup("");
				ret_last_token(*tokens)->value = str_add_strs_free((char *)(*tokens)->value, splitted, ' ');
				dfree((void **)splitted);
				show_token(*tokens);
				if (ft_strstr(gnl, return_missing_chars(data->_errcode)))
				{
					data->_errcode = 0;
					return ;
				}
				new_missing_prompt((char)data->_errcode);
				free(gnl);
			}
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
