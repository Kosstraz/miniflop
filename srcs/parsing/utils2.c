/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:40:38 by bama              #+#    #+#             */
/*   Updated: 2024/07/28 17:50:37 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 0 false
// 1 true
char	is_missing_septoktype(char _errcode)
{
	return (_errcode == SQUOTE_MISSING
		|| _errcode == DQUOTE_MISSING
		|| _errcode == PIPE_MISSING
		|| _errcode == AND_MISSING
		|| _errcode == OR_MISSING);
}

// Mets dans 'chars' le ou les caractères correspondant au code
// erreur donné. (Ex : si _errcode==AND_MISSING --> (*chars)="&&\0")
// Renvoie (*chars)
char	*return_missing_chars(char _errcode)
{
	static char	ret[3];

	ret[1] = 0;
	if (_errcode == SQUOTE_MISSING)
		ret[0] = '\'';
	else if (_errcode == DQUOTE_MISSING)
		ret[0] = '"';
	else if (_errcode == PIPE_MISSING)
		ret[0] = '|';
	else
	{
		if (_errcode == AND_MISSING)
		{
			ret[0] = '&';
			ret[1] = '&';
		}
		else if (_errcode == OR_MISSING)
		{
			ret[0] = '|';
			ret[1] = '|';
		}
	}
	ret[2] = 0;
	return (ret);
}
