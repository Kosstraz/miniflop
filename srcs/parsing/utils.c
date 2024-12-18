/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:40:38 by bama              #+#    #+#             */
/*   Updated: 2024/11/14 15:02:35 by ymanchon         ###   ########.fr       */
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

char	is_operand(char c[3])
{
	return (!ft_strncmp(c, "2>>", 3)
		|| (c[0] == '|' && c[1] != '|')
		|| (c[0] == '|' && c[1] == '|')
		|| (c[0] == '&' && c[1] == '&')
		|| (c[0] == '<' && c[1] != '<')
		|| (c[0] == '<' && c[1] == '<')
		|| (c[0] == '>' && c[1] != '>')
		|| (c[0] == '>' && c[1] == '>')
		|| (c[0] == '2' && c[1] == '>')
		|| (c[0] == ';')
		|| (c[0] == '(')
		|| (c[0] == ')'));
}

char	is_sep(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\0');
}

char	is_justsep_toktype(t_token tok)
{
	return (tok.type == Pipe || tok.type == And || tok.type == Or
		|| tok.type == Comma);
}

char	is_sep_toktype(t_token tok)
{
	return (tok.type == Pipe || tok.type == And || tok.type == Or
		|| tok.type == Comma || tok.type == Subshell);
}
