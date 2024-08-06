/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:08:41 by bama              #+#    #+#             */
/*   Updated: 2024/08/07 00:18:14 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_some_parsing(char ***splitted, const char *line, t_data *data)
{
	*splitted = ft_split_quotes(line, data);
	if (handle_generic_error(splitted, data) < 0)
		return ;
	place_envvars(splitted, data);
	separate_operands(splitted);
	//apply_wildcards(splitted);
	check_potential_errors(*splitted, data);
	if (handle_generic_error(splitted, data) < 0)
		return ;
	//*splitted = remove_useless_quotes(*splitted, data);
}

// Bon"jour mec MOUAH"AHAHH "why are you raging ??" "" A"urevoir "

static t_token	*parse_commandline(const char *line, t_data *data)
{
	char	**splitted;
	t_token	*token;
	t_token	*root;
	int		i;

	do_some_parsing(&splitted, line, data);
	if (!splitted)
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
	review_tokenid(&root);
	root = check_tokens_error(root, data);
	handle_generic_error(NULL, data);
	return (root);
}

void	take_commandline(const char *line, t_data *data)
{
	t_token	*tokens;

	if (!line)
		return ;
	tokens = parse_commandline(line, data);
	data->tokens = tokens;
	//show_token(tokens);
	if (data && data->tokens && data->tokens->value)
		exec(data);
}
