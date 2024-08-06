/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 01:14:40 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/06 21:17:02 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLATFORM_H
# define PLATFORM_H

# include <dirent.h>
# include <termcap.h>
# include <termios.h>

typedef enum e_type
{
	Null,
	Pipe,
	And,
	Or,
	Subshell,
	Command,
	Argument,
	RedirectW,
	RedirectR,
	RedirectAppend,
	HereDoc,
	Infile,
	Outfile,
	Errfile
}	t_e_type;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	enum e_type		type;
	const char		*value;
	struct s_token	*next;
}	t_token;

typedef struct s_coords
{
	int	l;
	int	c;
}	t_coords;

typedef struct s_line
{
	int			i;
	int			size;
	int			next;
	char		*buf;
	t_coords	last;
}	t_line;

typedef struct s_cap
{
	char	*cap;
	int		len;
}	t_cap;

typedef struct s_info
{
	int		cols;
	int		lines;
	t_cap	move;
	t_cap	clear;
	t_cap	left;
	t_cap	right;
	t_cap	save;
	t_cap	restore;
	t_cap	down;
	t_cap	up;
	t_cap	carriage;
}	t_info;

typedef struct s_term
{
	int				state;
	int				fd;
	char			*type;
	t_coords		curs;
	t_line			line;
	t_info			caps;
	struct termios	raw;
	struct termios	og;
}	t_term;

typedef struct s_data
{
	DIR		*dir;
	t_term	term;
	t_token	*tokens;
	t_env	*env;
	char	*prompt;
	char	exec_next;
	char	blt_val;
	int		npid;
	int		pids[NB_OF_PROC_MAX_PER_USER];
	int		fildes[2];
	int		fileno[3];
	int		_errcode;
	int		ret_cmd;
	int		historyfd;
}	t_data;

#endif
