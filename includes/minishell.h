/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:33:43 by bama              #+#    #+#             */
/*   Updated: 2024/07/29 19:53:26 by bama             ###   ########.fr       */
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

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
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
	Outfile
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

typedef struct s_data
{
	DIR		*dir;
	t_token	*tokens;
	t_env	*env;
	int		_errcode;
	int		historyfd;
}	t_data;

/*		BUILTINS		*/

int			ft_exit(char **av, t_data *data);
int			ft_cd(char **arguments);
int			ft_echo(char **arguments);

/*		MINISHELL		*/

void		minishell(char **env);
void		new_prompt(void);
void		free_data(t_data *data);
void		signals_handling(int signum);
void		add_env_to_data(t_data *data, char **env);
void		free_data(t_data *data);
void		init_data(t_data *data);
void		new_missing_prompt(char _errcode);

/*		PARSING			*/

void		print_env(t_env *env);
char		**remove_useless_quotes(char **splitted);
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

/*		DEBUG		*/

void		show_token(t_token *tok);

#endif