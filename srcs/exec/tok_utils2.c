/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:12:04 by bama              #+#    #+#             */
/*   Updated: 2024/08/02 18:17:40 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tok_next_redirect(t_token *cmdline)
{
	while (cmdline && !is_sep_toktype(*cmdline))
	{
		if (cmdline->type == RedirectW || cmdline->type == RedirectR
			|| cmdline->type == RedirectAppend)
			return (cmdline);
		cmdline = cmdline->next;
	}
	return (NULL);
}

// Regarde pour une ligne de commande, s'il y a une quelconque
// commande.
// 1 commande
// 0 aucune
char	is_there_cmd(t_token *cmdline)
{
	while (cmdline && !is_sep_toktype(*cmdline))
	{
		if (cmdline->type == Command)
			return (1);
		cmdline = cmdline->next;
	}
	return (0);
}
