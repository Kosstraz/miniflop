/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 01:14:40 by cachetra          #+#    #+#             */
/*   Updated: 2024/11/12 17:24:26 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLATFORM_H
# define PLATFORM_H

# include <dirent.h>
# include <termcap.h>
# include <termios.h>

typedef struct s_token	t_token;

typedef enum e_type
{
	Null,
	Comma,
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


// dirjok[1024] is a list of directories
// lastfromrecu is the last token from the recursion
// at is the index of the current directory
// dirslen is the length of strings in 'char **dirs'
// judge is the result of inspect_a_file()
	// 1 : joker is valid
	// 0 : joker is invalid
// first is to now if the first character is a joker
// last is to now if the last character is a joker
// single is to now if there is only joker
// words is the result of ft_split_quotes('*')
// dirs is the result of ft_split_quotes('/')
// save is the original string before the recursion, and the current string during the recursion
	// but we need to restore the original string after the recursion
// dir is the total directory string name
typedef struct s_joker
{
	DIR		*dijok[1024];
	t_token	*lastfromrecu;
	size_t	at;
	size_t	dirslen;
	BOOL	judge;
	BOOL	first;
	BOOL	last;
	BOOL	single;
	BOOL	absolute;
	char	**words;
	char	**dirs;
	char	*save;
	char	*dir;
}	t_joker;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			joker;
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
	int			total;
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

typedef struct s_tab
{
	char			is_on;
	int				max_cnt;
	int				max_len;
	int				pos;
	int				cnt;
	int				written;
	char			*ref;
	char			*dir;
	unsigned char	types[S_CHUNK];
	char			files[S_CHUNK][S_CHUNK];
}	t_tab;

typedef struct s_term
{
	int				state;
	int				fd;
	char			*type;
	t_tab			tab;
	t_coords		curs;
	t_line			line;
	t_info			caps;
	struct termios	raw;
	struct termios	og;
}	t_term;

typedef struct s_history
{
	char				*line;
	struct s_history	*next;
}	t_history;

typedef struct s_history_info
{
	t_history	*info;
	char		*original_line;
	char		original_line_set;
	int			nb_of_line_searched;
	int			current_line;
}	t_history_info;

typedef struct s_data
{
	DIR				*dir;
	t_term			term;
	t_token			*tokens;
	t_env			*env;
	t_history_info	history;
	char			*prompt;
	char			exec_next;
	char			blt_val;
	int				npid;
	int				pids[NB_OF_PROC_MAX_PER_USER];
	int				tmpFildes[2];
	int				fildes[2];
	int				fileno[3];
	int				_errcode;
	int				ret_cmd;
	int				historyfd;
	char			(*_is_sep_)(char);
	char			last_is_pipe;
	char			firstcmd;
}	t_data;

#endif
