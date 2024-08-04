/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <cachetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:33:43 by bama              #+#    #+#             */
/*   Updated: 2024/08/03 21:50:51 by cachetra         ###   ########.fr       */
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
#  define ARG_MAX	2087151
# endif

// ARG_MAX / 2
# define SZ_MAX		1174302

# define ECHO_BLT	1
# define UNSET_BLT	2
# define CD_BLT		3
# define EXIT_BLT	4
# define EXPORT_BLT	5
# define ENV_BLT	6
# define PWD_BLT	7

# define FORKED		1

# define KEY_DEL	"\033[3~"
# define KEY_UP		"\033[A"
# define KEY_DOWN	"\033[B"
# define KEY_RIGHT	"\033[C"
# define KEY_LEFT	"\033[D"

# define READ	16
# define CHUNK	256
# define TERM	4096

# define CANON	0
# define RAW	1

# define LEFT	-1
# define RIGHT	1

# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include "error.h"
# include "libft.h"
# include "platform.h"

/*		DEzBUG		*/

void		show_token(t_token *tok);

/* **************************************************** */
/*														*/
/*		 __ __| __|  _ \   \  |   __|    \    _ \		*/
/*		    |   _|     /  |\/ |  (      _ \   __/		*/
/*		   _|  ___| _|_\ _|  _| \___| _/  _\ _|			*/
/*														*/
/* **************************************************** */

void		kill_term(t_data *data);
void		term_init(t_data *data) __attribute__((cold));
void		term_set_raw(t_data *data);
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
// void		print_chars(t_data *data, char *chars, int cnt)
void		print_char(t_data *data, int c)
			__attribute__((hot));
void		key_backspace(t_data *data) __attribute__((hot));
void		key_delete(t_data *data) __attribute__((hot));
void		key_tab(t_data *data) __attribute__((hot));
void		key_up(t_data *data) __attribute__((hot));
void		key_down(t_data *data) __attribute__((hot));
void		key_right(t_data *data) __attribute__((hot));
void		key_left(t_data *data) __attribute__((hot));
void		free_term(t_data *data) __attribute__((cold));

int			ft_read(int fd, char *buf, int size, t_data *data);

char		*handle_interrupt(t_data *data);
char		*ft_readline(char *prompt, t_data *data) __attribute__((hot));

/* **************************************************** */
/*														*/
/*  		_ \  \    _ \   __| _ _|   \ |   __|		*/
/*  		__/ _ \     / \__ \   |   .  |  (_ |		*/
/*		   _| _/  _\ _|_\ ____/ ___| _|\_| \___|		*/
/*														*/
/* **************************************************** */

void		reset_commandtype(t_token **root);
void		print_env(t_env *env);
void		take_commandline(const char *line, t_data *data);
void		free_tokens(t_token **root);
void		place_envvars(char ***splitted);
void		apply_wildcards(char ***splitted);
void		separate_operands(char ***splitted);
void		check_quote_status(char c, char *opened_status);
void		check_e_type(t_token **second, const char *word, int i);
void		review_tokenid(t_token **tokens);
void		detect_redirect_type(t_token **tok);

char		is_operand(char c[2]);
char		is_sep(char c);
char		is_sep_toktype(t_token tok);
char		is_missing_septoktype(int _errcode);
char		*return_missing_chars(char _errcode);

t_token		*new_token(char *value);
t_token		*ret_last_token(t_token *tokens);

char		**remove_useless_quotes(char **splitted, t_data *data);
char		**ft_split_quotes(const char *s, t_data *data);

/* ******************************************************** */
/*															*/
/*		  _ )  |  | _ _|  |  __ __| _ _|   \ |   __|		*/
/*		  _ \  |  |   |   |     |     |   .  | \__ \		*/
/*		 ___/ \__/  ___| ____| _|   ___| _|\_| ____/		*/
/*															*/
/* ******************************************************** */

int			export_args(char **args, t_env **head);
int			ft_cd(char **arguments, t_data *data);
int			ft_echo(char **arguments, t_data *data);
int			ft_env(char **args, t_data *data);
int			ft_exit(char **av, t_data *data);
int			ft_export(char **args, t_data *data);
int			ft_pwd(char **args, t_data *data);
int			ft_unset(char **arguments, t_data *data);

/* **************************************************************** */
/*																	*/
/*		  __| \ \  /  __|   __|  |  | __ __| _ _|   _ \   \ |		*/
/*		  _|   >  <   _|   (     |  |    |     |   (   | .  |		*/
/*		 ___|  _/\_\ ___| \___| \__/    _|   ___| \___/ _|\_|		*/
/*																	*/
/* **************************************************************** */

void		dup2_stdin(int fd[2]);
void		dup2_stdout(int fd[2]);
void		fprint_invalidcmd(t_token *cmdline);
void		save_stdfileno(int fileno_[3]);
void		restore_stdfileno(int fileno_[3]);
void		exec(t_data *data);

char		is_there_cmd(t_token *cmdline);
char		is_there_redirect(t_token *cmdline);
char		check_exitedchild(t_data *data, int *status);
char		is_a_builtin(t_token *cmdline);

int			exec_builtins(char blt_val, t_data *data, t_token *cmdline);

t_e_type	tok_next_type(t_token *last);

char		*getcmdpath(t_token *cmdline, t_data *data);

t_token		*tok_next_redirect(t_token *cmdline);
t_token		*tok_next_cmd(t_token *last);
t_token		*tok_next_sep(t_token *last);

char		**convert_env(t_env *env);
char		**tok_to_strs(t_token *cmdline);

/* ************************************************ */
/*													*/
/*		   __|  __|   \ |  __|  _ \    \    |		*/
/*		  (_ |  _|   .  |  _|     /   _ \   |		*/
/*		 \___| ___| _|\_| ___| _|_\ _/  _\ ___|		*/
/*													*/
/* ************************************************ */

void		exit_shell(char *mess, t_data *data, int status);
void		increment_shlvl(t_env **env);
void		free_env(t_env **env);
void		free_shell(t_data *data);
void		minishell(char **env);
void		new_prompt(char **buffer_prompt);
void		free_data(t_data *data);
void		signals_handling(int signum);
void		add_env_to_data(t_data *data, char **env);
void		free_data(t_data *data);
void		init_data(t_data *data);
void		new_missing_prompt(char _errcode);

char		*getenvval(char *envname, t_env *env);

int			setenvval(char *envname, char *newval, t_env **env);

#endif
