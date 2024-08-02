/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:08:41 by bama              #+#    #+#             */
/*   Updated: 2024/08/02 20:16:57 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_some_parsing(char ***splitted, const char *line, t_data *data)
{
	*splitted = ft_split_quotes(line, data);
	place_envvars(splitted);
	separate_operands(splitted);
	apply_wildcards(splitted);
	*splitted = remove_useless_quotes(*splitted, data);
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

/*static char	unfinished_prompt(char *line, char ***splitted,
			int errcode_tmp, t_token **tokens)
{
	if ((*splitted) && !(*splitted)[0])
		(*splitted)[0] = ft_strdup("");
	//free(ret_last_token(*tokens)->value);
	ret_last_token(*tokens)->value = str_add_strs_free(
		(char *)(*tokens)->value, (*splitted), ' ', '\n');
	dfree((void **)(*splitted));
	show_token(*tokens);
	if (ft_strstr(line, return_missing_chars(errcode_tmp)))
		return (1);
	new_missing_prompt((char)errcode_tmp);
	free(line);
	return (0);
}*/

/*static void	maybe_prompt(t_data *data, t_token **tokens)
{
	char	**splitted;
	char	*gnl;
	int		errcode_tmp;

	if (data->_errcode < 0)
	{
		errcode_tmp = data->_errcode;
		new_missing_prompt((char)data->_errcode);
		gnl = get_next_line(STDIN_FILENO);
		while (!g_sig)
		{
			if (gnl)
			{
				do_some_parsing(&splitted, gnl, data);
				if (unfinished_prompt(gnl, &splitted, errcode_tmp, tokens))
					return ;
			}
			gnl = get_next_line(STDIN_FILENO);
		}
		free(gnl);
		data->_errcode = 0;
	}
}*/

void	take_commandline(const char *line, t_data *data)
{
	t_token	*tokens;

	tokens = parse_commandline(line, data);
	data->tokens = tokens;
	show_token(tokens);
	//while (is_missing_septoktype(data->_errcode))
		//maybe_prompt(data, &tokens);
	if (data && data->tokens && data->tokens->value)
		exec(data);
}
