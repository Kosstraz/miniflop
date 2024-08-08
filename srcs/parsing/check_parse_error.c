/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:40:32 by bama              #+#    #+#             */
/*   Updated: 2024/08/07 16:31:02 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_gen_subshell_error(t_data *data)
{
	if (data->_errcode == SUBSHELL_MISSING)
		write(2, SUBSHELL_ERROR, ft_strlen(SUBSHELL_ERROR));
	else if (data->_errcode == SUBSHELL_INVALID)
		write(2, SUBSHELLI_ERROR, ft_strlen(SUBSHELLI_ERROR));
	else if (data->_errcode == SUBSHELL_USELESS)
		write(2, SUBSHELLU_ERROR, ft_strlen(SUBSHELLU_ERROR));
}

char	handle_generic_error(char ***splitted, t_data *data)
{
	if (data->_errcode == SQUOTE_MISSING)
		write(2, SQUOTE_ERROR, ft_strlen(SQUOTE_ERROR));
	else if (data->_errcode == DQUOTE_MISSING)
		write(2, DQUOTE_ERROR, ft_strlen(DQUOTE_ERROR));
	handle_gen_subshell_error(data);
	if (data->_errcode == INCOMPLETE_PIPE)
		write(2, PIPE_ERROR, ft_strlen(PIPE_ERROR));
	else if (data->_errcode == INCOMPLETE_AND)
		write(2, AND_ERROR, ft_strlen(AND_ERROR));
	else if (data->_errcode == INCOMPLETE_OR)
		write(2, OR_ERROR, ft_strlen(OR_ERROR));
	if (data->_errcode <= SQUOTE_MISSING
		&& data->_errcode >= INCOMPLETE_OR)
	{
		if (splitted)
		{
			dfree((void **)*splitted);
			*splitted = NULL;
		}
		return (data->_errcode);
	}
	return (0);
}

void	check_potential_errors(char **splitted, t_data *data)
{
	char	*lastw;

	lastw = lastword(splitted);
	if (!ft_strcmp(lastw, "|"))
		data->_errcode = INCOMPLETE_PIPE;
	else if (!ft_strcmp(lastw, "&&"))
		data->_errcode = INCOMPLETE_AND;
	else if (!ft_strcmp(lastw, "||"))
		data->_errcode = INCOMPLETE_OR;
}

t_token	*check_tokens_error(t_token *tokens, t_data *data)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		is_there_subshells(tmp, data);
		if (data->_errcode <= SQUOTE_MISSING
			&& data->_errcode >= INCOMPLETE_OR)
			return (NULL);
		tmp = tok_skip_subshell(tmp);
	}
	return (tokens);
}
