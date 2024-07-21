/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_id2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:17:54 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 22:45:59 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	detect_redirect_type(t_token **tok)
{
	if (!ft_strcmp((*tok)->value, "<"))
	{
		(*tok)->type = Redirect;
		(*tok)->next->type = Infile;
	}
	else if (!ft_strcmp((*tok)->value, ">"))
	{
		(*tok)->type = Redirect;
		(*tok)->next->type = Outfile;
	}
	else if (!ft_strcmp((*tok)->value, ">>"))
	{
		(*tok)->type = RedirectAppend;
		(*tok)->next->type = Outfile;
	}
	else if (!ft_strcmp((*tok)->value, "<<"))
	{
		(*tok)->type = Redirect;
		(*tok)->next->type = HereDoc;
	}
}
