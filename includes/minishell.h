/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:33:43 by bama              #+#    #+#             */
/*   Updated: 2024/08/01 14:17:38 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT1 "\e[1m\e[35m"
# define PROMPT1_SIZE 9

# define PROMPT2 " $> "
# define PROMPT2_SIZE 4

# define PROMPT3 "\e[0m"
# define PROMPT3_SIZE 4

# define SQUOTE_PROMPT "\e[1msquote >>> \e[0m"
# define SQUOTE_PROMPT_SIZE 19

# define DQUOTE_PROMPT "\e[1mdquote >>> \e[0m"
# define DQUOTE_PROMPT_SIZE 19

# define PIPE_PROMPT "\e[1mpipe >>> \e[0m"
# define PIPE_PROMPT_SIZE 18

# define AND_PROMPT "\e[1mand >>> \e[0m"
# define AND_PROMPT_SIZE 16

# define OR_PROMPT "\e[1mor >>> \e[0m"
# define OR_PROMPT_SIZE 15

# define EXIT_TEXT "\e[31m\nexit\n\e[0m"
# define EXIT_TEXT_SIZE 15

# ifndef ARG_MAX
#  define ARG_MAX 2087151
# endif

# define ECHO_BLT	1
# define UNSET_BLT	2
# define CD_BLT		3
# define EXIT_BLT	4

# define FORKED		1

# define TAB '\011'
# define BCK '\177'
# define DEL "\033[3~"
# define KEY_UP "\033[A"
# define KEY_DOWN "\033[B"
# define KEY_RIGHT "\033[C"
# define KEY_LEFT "\033[D"

# define READ 16
# define CHUNK 256
# define TERM 4096

# define ORIGINAL 0
# define RAW 1

# define LEFT -1
# define RIGHT 1

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termcap.h>
# include <termios.h>
# include "error.h"
# include "libft.h"

extern char				g_sig;

typedef unsigned int	t_uint;
typedef long long		t_ll;

typedef enum e_type
{
	Null,
	Pipe,
	And,
	Or,
	Command,
	Argument,
	Redirect,
	RedirectAppend,
	HereDoc,
	Infile,
	Outfile,
	Errfile
}	t_e_type;

typedef struct s_vec2ul
{
	size_t	x;
	size_t	y;
}	t_vec2ul;

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
	int		fildes[2];
	int		_errcode;
	int		ret_cmd;
	int		historyfd;
}	t_data;

/*		BUILTINS		*/

int			ft_unset(char **arguments, t_data *data);
int			ft_exit(char **av, t_data *data);
int			ft_cd(char **arguments, t_data *data);
int			ft_echo(char **arguments, t_data *data);

/*		   EXEC	    	*/

char		check_exitedchild(int *status);
void		fprint_invalidcmd(const char *cmdword);
void		save_stdfileno(int fileno_[3]);
void		restore_stdfileno(int fileno_[3]);
char		*search_cmd(t_token *cmdline, t_data *data);
void		execution(t_data *data);
char		is_a_builtin(const char *cmd);
char		**convert_env(t_env *env);
t_token		*tok_next_cmd(t_token *last);
t_token		*tok_next_sep(t_token *last);
char		**tok_to_strs(t_token *cmdline);

/*		PARSING			*/

void		reset_commandtype(t_token **root);
void		print_env(t_env *env);
char		**remove_useless_quotes(char **splitted, t_data *data);
char		**ft_split_quotes(const char *s, t_data *data);
void		take_commandline(const char *line, t_data *data);
t_token		*new_token(char *value);
void		free_tokens(t_token **root);
void		place_envvars(char ***splitted);
t_vec2ul	new_vec2ul(size_t x, size_t y);
void		apply_wildcards(char ***splitted);
void		separate_operands(char ***splitted);
void		check_quote_status(char c, char *opened_status);
char		is_operand(char c[2]);
char		is_sep(char c);
void		check_e_type(t_token **second, const char *word, int i);
void		review_tokenid(t_token **tokens);
char		is_sep_toktype(t_token tok);
void		detect_redirect_type(t_token **tok);
char		is_missing_septoktype(int _errcode);
char		*return_missing_chars(char _errcode);
t_token		*ret_last_token(t_token *tokens);

/*		MINISHELL		*/

void		increment_shlvl(t_env **env);
void		free_env(t_env **env);
void		free_shell(t_data *data);
char		*getenvval(char *envname, t_env *env);
int			setenvval(char *envname, char *newval, t_env **env);
void		minishell(char **env);
void		new_prompt(char **buffer_prompt);
void		free_data(t_data *data);
void		signals_handling(int signum);
void		add_env_to_data(t_data *data, char **env);
void		free_data(t_data *data);
void		init_data(t_data *data);
void		new_missing_prompt(char _errcode);

/*		TERMCAP			*/
void		term_init(t_data *data) __attribute__((cold));
char		*ft_readline(char *prompt, t_data *data) __attribute__((hot));
void		term_reset(t_data *data) __attribute__((cold));
void		*ft_malloc(size_t size, t_data *data) __attribute__((cold));
void		*ft_realloc(void *ptr, size_t sze,
				t_data *data) __attribute__((cold));
void		update_last(t_term *term, int add) __attribute__((hot));
void		update_position(t_term *term, int dir) __attribute__((hot));
void		get_cursor_position(t_data *data) __attribute__((cold));
void		move_up(t_data *data, int last_col);
void		move_down(t_term *term, int first_col);
void		write_stored(t_term *term, int at, char *mem) __attribute__((hot));
void		print_char(t_data *data, int c);
void		key_backspace(t_data *data) __attribute__((hot));
void		key_delete(t_data *data) __attribute__((hot));
void		key_tab(t_data *data) __attribute__((hot));
void		key_up(t_data *data) __attribute__((hot));
void		key_down(t_data *data) __attribute__((hot));
void		key_right(t_data *data) __attribute__((hot));
void		key_left(t_data *data) __attribute__((hot));
void		free_term(t_data *data) __attribute__((cold));

/*		DEBUG		*/

void		show_token(t_token *tok);

#endif
