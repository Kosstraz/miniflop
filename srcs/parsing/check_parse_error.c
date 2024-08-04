/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:40:32 by bama              #+#    #+#             */
/*   Updated: 2024/08/04 17:22:14 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_generic_error(char ***splitted, t_data *data)
{
	if (data->_errcode == SQUOTE_MISSING)
		write(1, SQUOTE_ERROR, ft_strlen(SQUOTE_ERROR));
	else if (data->_errcode == DQUOTE_MISSING)
		write(1, DQUOTE_ERROR, ft_strlen(DQUOTE_ERROR));
	else if (data->_errcode == SUBSHELL_MISSING)
		write(1, SUBSHELL_ERROR, ft_strlen(SUBSHELL_ERROR));
	else if (data->_errcode == INCOMPLETE_PIPE)
		write(1, PIPE_ERROR, ft_strlen(PIPE_ERROR));
	else if (data->_errcode == INCOMPLETE_AND)
		write(1, AND_ERROR, ft_strlen(AND_ERROR));
	else if (data->_errcode == INCOMPLETE_OR)
		write(1, OR_ERROR, ft_strlen(OR_ERROR));
	if (data->_errcode <= SQUOTE_MISSING
		&& data->_errcode >= INCOMPLETE_OR)
	{
		dfree((void **)*splitted);
		*splitted = NULL;
		return (data->_errcode);
	}
	return (0);
}

char	check_parse_error(char ***splitted, t_data *data)
{
	char	ret;

	ret = check_generic_error(splitted, data);
	if (ret < 0)
		return (ret);
	return (0);
}

void	check_tokens_error(t_token *tokens, t_data *data)
{
	(void)tokens;
}
