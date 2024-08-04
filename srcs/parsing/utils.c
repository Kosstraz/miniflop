/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:40:38 by bama              #+#    #+#             */
/*   Updated: 2024/08/04 15:20:11 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Put this function at the start of a loop
// (opened_status == 0) closed
// (opened_status == 1) single-quotes opened
// (opened_status == 2) double-quotes opened
// If your loop is finished but (opened_status != 0) -->
//--> a closing quote is missing
void	check_quote_status(char c, char *opened_status)
{
	if (!*opened_status && c == '\'')
		*opened_status = 1;
	else if (!*opened_status && c == '"')
		*opened_status = 2;
	else if ((*opened_status == 1 && c == '\'')
		|| (*opened_status == 2 && c == '"'))
		*opened_status = 0;
}

char	is_operand(char c[2])
{
	return ((c[0] == '|' && c[1] != '|')
		|| (c[0] == '|' && c[1] == '|')
		|| (c[0] == '&' && c[1] == '&')
		|| (c[0] == '<' && c[1] != '<')
		|| (c[0] == '<' && c[1] == '<')
		|| (c[0] == '>' && c[1] != '>')
		|| (c[0] == '>' && c[1] == '>')
		|| (c[0] == '2' && c[1] == '>'));
}

char	is_sep(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char	is_sep_toktype(t_token tok)
{
	return (tok.type == Pipe || tok.type == And || tok.type == Or);
}
