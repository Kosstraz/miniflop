/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:08:41 by bama              #+#    #+#             */
/*   Updated: 2024/11/13 17:32:55 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_some_parsing(char ***splitted, const char *line, t_data *data)
{
	*splitted = ft_split_quotes(line, is_sep, data);
	if (handle_generic_error(splitted, data) < 0)
		return ;
	else if (handle_when_sep_is_first(splitted, data) < 0)
		return ;
	place_envvars(splitted, data);
	separate_operands(splitted);
	check_potential_errors(*splitted, data);
	if (handle_generic_error(splitted, data) < 0)
		return ;
}

static t_token	*parse_commandline(const char *line, t_data *data)
{
	char	**splitted;
	t_token	*token;
	t_token	*root;
	int		i;

	do_some_parsing(&splitted, line, data);
	if (!splitted || !splitted[0])
		return (NULL);
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
	jokeroverride(&root, data);
	review_tokenid(&root);
	root = check_tokens_error(root, data);
	handle_gen_subshell_error(data);
	remove_useless_quotes(&root, data);
	return (root);
}

void	take_commandline(const char *line, t_data *data)
{
	t_token	*tokens;

	if (!line)
		return ;
	tokens = parse_commandline(line, data);
	show_token(tokens);
	data->tokens = tokens;
	if (data && data->tokens && data->tokens->value)
		exec(data);
	add_to_history((char *)line, data);
}
