/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:40:32 by bama              #+#    #+#             */
/*   Updated: 2024/11/17 16:10:54 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	handle_when_sep_is_first(char ***splitted)
{
	char	status;

	status = 0;
	if (!splitted || !*splitted)
		return (-PARSE_ERROR);
	else if (!ft_strcmp((*splitted)[0], "|"))
		status = PARSE_ERROR;
	else if (!ft_strcmp((*splitted)[0], "&&"))
		status = PARSE_ERROR;
	else if (!ft_strcmp((*splitted)[0], "||"))
		status = PARSE_ERROR;
	else if (!ft_strcmp((*splitted)[0], ";"))
		status = PARSE_ERROR;
	if (status == PARSE_ERROR)
	{
		write(1, PARSE_ERROR_T, PARSE_ERROR_SIZE);
		dfree((void *)*splitted);
		*splitted = NULL;
	}
	return (-status);
}

void	handle_gen_subshell_error(t_data *data)
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
	else if (data->_errcode == INCOMPLETE_COMMA)
		write(2, COMMA_ERROR, ft_strlen(COMMA_ERROR));
	if (data->_errcode <= SQUOTE_MISSING
		&& data->_errcode >= INCOMPLETE_COMMA)
	{
		if (splitted)
		{
			dfree((void **)*splitted);
			*splitted = NULL;
		}
		return (data->_errcode);
	}
	return (data->_errcode);
}

void	check_potential_errors(char **splitted, t_data *data)
{
	char	*lastw;
	char	*blastw;

	lastw = lastword(splitted);
	blastw = before_lastword(splitted);
	if (!ft_strcmp(lastw, "|"))
		data->_errcode = INCOMPLETE_PIPE;
	else if (!ft_strcmp(lastw, "&&"))
		data->_errcode = INCOMPLETE_AND;
	else if (!ft_strcmp(lastw, "||"))
		data->_errcode = INCOMPLETE_OR;
	else if (!ft_strcmp(blastw, ";") && !ft_strcmp(lastw, ";"))
		data->_errcode = INCOMPLETE_COMMA;
}

t_token	*check_tokens_error(t_token **tokens, t_data *data)
{
	is_there_subshells(*tokens, data);
	handle_generic_error(NULL, data);
	if (data->_errcode <= SQUOTE_MISSING
		&& data->_errcode >= INCOMPLETE_COMMA)
	{
		free_tokens(tokens);
		*tokens = NULL;
	}
	return (*tokens);
}
