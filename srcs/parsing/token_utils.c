/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:48:31 by bama              #+#    #+#             */
/*   Updated: 2024/08/11 15:48:33 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_token(t_token **after_it, t_token *new)
{
	t_token	*tmp;

	if (!after_it)
		return ;
	else if (!(*after_it))
		*after_it = new;
	else if (*after_it)
	{
		if (!(*after_it)->next)
			(*after_it)->next = new;
		else
		{
			tmp = (*after_it)->next;
			(*after_it)->next = new;
			while (new->next)
				new = new->next;
			new->next = tmp;	
		}
	}
}

void	delete_token(t_token **root, t_token **to_del)
{
	t_token	*tmpdel;
	t_token	*tmproot;
	t_token	*prev;

	tmpdel = *to_del;
	tmproot = *root;
	prev = NULL;
	while (tmproot)
	{
		if (tmproot == tmpdel)
		{
			if (!prev)
			{
				free((char *)tmproot->value);
				*root = (*root)->next;
				free(tmproot);
				*to_del = NULL;
				return ;
			}
			else
			{
				prev->next = tmproot->next;
				free((char *)tmproot->value);
				free(tmproot);
				*to_del = NULL;
				return ;
			}
		}
		prev = tmproot;
		tmproot = tmproot->next;
	}
}

