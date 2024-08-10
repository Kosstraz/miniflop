/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_initialise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:49:47 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/10 01:52:57 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	term_set_raw(t_data *data)
{
	int	log;

	log = tcgetattr(data->term.fd, &data->term.raw);
	if (log)
		exit_shell("\e[1;32mtcgetattr\e[0m", data, EXIT_FAILURE);
	data->term.og = data->term.raw;
	data->term.raw.c_lflag = ~(ECHO | ICANON | ISIG);
	data->term.raw.c_cc[VTIME] = 0;
	data->term.raw.c_cc[VMIN] = 1;
	log = tcsetattr(data->term.fd, TCSANOW, &data->term.raw);
	if (log)
		exit_shell("\e[1;32mtcsetattr\e[0m", data, EXIT_FAILURE);
	data->term.state = RAW;
}

static void	term_set_zero(t_term *term)
{
	term->fd = 0;
	term->type = NULL;
	term->state = CANON;
	term->curs.c = 0;
	term->curs.l = 0;
	term->caps.cols = 0;
	term->caps.lines = 0;
	term->line.i = 0;
	term->line.size = 0;
	term->line.next = 0;
	term->line.total = B_CHUNK;
	term->line.last.c = 0;
	term->line.last.l = 0;
	term->line.buf = NULL;
	term->tab.is_on = 0;
	term->tab.max_cnt = 0;
	term->tab.max_len = 0;
	term->tab.cnt = 0;
	term->tab.written = 0;
	term->tab.dir = NULL;
	term->tab.pos = -1;
	term->tab.ref = NULL;
	ft_memset(term->tab.types, 0, sizeof(int) * S_CHUNK);
	ft_memset(term->tab.files, 0, sizeof(char) * S_CHUNK * S_CHUNK);
}

static t_cap	ft_tgetstr(char *id, char **area, t_data *data)
{
	t_cap	new;

	new.cap = tgetstr(id, area);
	if (!new.cap)
		exit_shell("\e[1;32mtgetstr\e[0m", data, EXIT_FAILURE);
	new.len = ft_strlen(new.cap);
	return (new);
}

static void	get_termcaps(t_data *data)
{
	data->term.caps.lines = tgetnum("li");
	data->term.caps.cols = tgetnum("co");
	data->term.caps.move = ft_tgetstr("cm", NULL, data);
	data->term.caps.clear = ft_tgetstr("cd", NULL, data);
	data->term.caps.left = ft_tgetstr("le", NULL, data);
	data->term.caps.right = ft_tgetstr("nd", NULL, data);
	data->term.caps.save = ft_tgetstr("sc", NULL, data);
	data->term.caps.restore = ft_tgetstr("rc", NULL, data);
	data->term.caps.down = ft_tgetstr("do", NULL, data);
	data->term.caps.up = ft_tgetstr("up", NULL, data);
	data->term.caps.carriage = ft_tgetstr("cr", NULL, data);
}

void	term_init(t_data *data, char **env)
{
	int		log;
	char	buffer[TERM];

	term_set_zero(&data->term);
	if (!env || !*env)
		data->term.type = ft_strdup(DEFAULT_TERM);//a free si !env ou !*env
	else
		data->term.type = getenv("TERM");
	if (!data->term.type)
		exit_shell("\e[1;31mgetenv\e[0m", data, EXIT_FAILURE);
	log = tgetent(buffer, data->term.type);
	if (log != 1)
		exit_shell("\e[1;31mtgetent\e[0m", data, EXIT_FAILURE);
	data->term.fd = ttyslot();
	if (!isatty(data->term.fd))
		exit_shell("\e[1;31mttyslot\e[0m", data, EXIT_FAILURE);
	get_termcaps(data);
	term_set_raw(data);
}
