/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:48:31 by bama              #+#    #+#             */
/*   Updated: 2024/08/08 02:32:23 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_newtoken_next(char *value, t_token **prev)
{
	t_token	*tofree;
	t_token	*tmp;

	tmp = *prev;
	if (!tmp)
	{
		*prev = new_token(value);
		(*prev)->type = Argument;
	}
	else if (tmp->next)
	{
		tofree = (*prev)->next;
		(*prev)->next = new_token(value);
		(*prev)->next->type = tofree->type;
		(*prev)->next->next = tofree->next;
		free(tofree);
	}
	else if (!tmp->next)
	{
		tmp->next = new_token(value);
		tmp->type = Argument;
	}
}
