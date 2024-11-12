/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:53:14 by bama              #+#    #+#             */
/*   Updated: 2024/11/12 15:11:24 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_readredirection(t_token *r, t_data *data)
{
	char	*heredoc_prompt;
	//char	*heredoc_eof;
	char	*gnl;
	int		fd;

	if (r->next && r->next->type == HereDoc)
	{
		fd = STDIN_FILENO;
		new_prompt_heredoc(&heredoc_prompt, data);
		write(1, heredoc_prompt, ft_strlen(heredoc_prompt));
		free(heredoc_prompt);
		gnl = get_next_line(fd);
		while (gnl)
		{
			free(gnl);
			new_prompt_heredoc(&heredoc_prompt, data);
			write(1, heredoc_prompt, ft_strlen(heredoc_prompt));
			free(heredoc_prompt);
			gnl = get_next_line(fd);
		}
	}
	else
	{
		fd = open(r->next->value, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return ;
}

static void	do_errredirection(t_token *r)
{
	int	fd;

	if (r->type == RedirectW)
		fd = open(r->next->value, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (r->type == RedirectAppend)
		fd = open(r->next->value, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else
		return ;
	dup2(fd, STDERR_FILENO);
	close(fd);
}

static void	do_writeredirection(t_token *r, t_data *data)
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
	r->next->value = "daw";
	if (fd == -1)
	{
		ft_printf("%s%s%s%s%s%s%s", INVALIDFILE_PRINTF1,
			CURLY, LINE_RED, r->next->value, RESET,
			BOLD, INVALIDFILE_PRINTF2);
		exit_shell("file can not be opened\n", data, 1);
	}
	dup2(fd, std);
	close(fd);
}

void	do_redirections(t_data *data, t_token *cmdline, int mode)
{
	t_token	*r;

	r = tok_next_redirect(cmdline);
	while (r)
	{
		if (mode == O_RDONLY && r->type == RedirectR)
			do_readredirection(r, data);
		else if (mode == O_WRONLY && r->next && r->next->type == Errfile)
			do_errredirection(r);
		else if (mode == O_WRONLY)
			do_writeredirection(r, data);
		r = tok_next_redirect(r->next);
	}
}
