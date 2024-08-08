/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:53:14 by bama              #+#    #+#             */
/*   Updated: 2024/08/07 13:42:56 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_readredirection(t_token *r)
{
	int	fd;

	fd = open(r->next->value, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return ;
}

static void	do_errredirection(t_token *r)
{
	int	fd;

	if (r->type == RedirectW)
		fd = open(r->next->value, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (r->type == RedirectAppend)
		fd = open(r->next->value, O_WRONLY | O_APPEND | O_CREAT, 0666);
	dup2(fd, STDERR_FILENO);
	close(fd);
}

static void	do_writeredirection(t_token *r)
{
	int	fd;
	int	std;

	if (r->type == RedirectW)
		fd = open(r->next->value, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (r->type == RedirectAppend)
		fd = open(r->next->value, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else
		return ;
	if (r->next->type == Errfile)
		std = STDERR_FILENO;
	else
		std = STDOUT_FILENO;
	dup2(fd, std);
	close(fd);
}

void	do_redirections(t_token *cmdline, int mode)
{
	t_token	*r;

	r = tok_next_redirect(cmdline);
	if (mode == O_RDONLY && r->type == RedirectR)
		do_readredirection(r);
	else if (mode == O_WRONLY && r->next && r->next->type == Errfile)
		do_errredirection(r);
	else if (mode == O_WRONLY)
		do_writeredirection(r);
}
