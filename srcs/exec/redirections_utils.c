/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:53:14 by bama              #+#    #+#             */
/*   Updated: 2024/11/29 17:10:46 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_readredirection(t_token *r, t_data *data)
{
	char	*heredoc_prompt;
	char	*line;
	t_data	tmp;
	int		fd;

	if (r->next && r->next->type == HereDoc)
	{
		fd = fork();
		if (fd == 0)
		{
			tmp = *data;
			line = NULL;
			new_prompt_heredoc(&heredoc_prompt, data);
			while (ft_strcmp(line, r->next->value) && ft_strcmp(line, "\003"))
			{
				free(line);
				init_data(data);	
				data->heredoc_is_active = TRUE;
				if (data->term.state == CANON)
					term_set_raw(data);
				line = ft_readline(heredoc_prompt, data);
				term_reset(data);
			}
			free(heredoc_prompt);
			write(data->term.fd, "\n", 1);
			*data = tmp;
			data->heredoc_is_active = FALSE;
			exit(data->ret_cmd);
		}
		waitpid(fd, NULL, 0);
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
