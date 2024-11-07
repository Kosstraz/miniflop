/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:33:43 by bama              #+#    #+#             */
/*   Updated: 2024/11/07 19:00:16 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termcap.h>
# include <termios.h>
# include "colors.h"
# include "defs.h"
# include "error.h"
# include "libft.h"
# include "platform.h"

// extern char	g_sig;

/* ************************************************ */
/*													*/
/*		   __|  __|   \ |  __|  _ \    \    |		*/
/*		  (_ |  _|   .  |  _|     /   _ \   |		*/
/*		 \___| ___| _|\_| ___| _|_\ _/  _\ ___|		*/
/*													*/
/* ************************************************ */

void		new_prompt_heredoc(char **buffer_prompt, t_data *data);
void		create_own_env(t_data *data);
void		initialise_env(t_data *data);
void		env_remove(char *name, t_env **env);
void		exit_shell(char *mess, t_data *data, int status);
void		increment_shlvl(t_env **env);
void		free_env(t_env **env);
void		free_shell(t_data *data);
void		minishell(char **env);
void		new_prompt(char **buffer_prompt, t_data *data);
void		add_new_env(char *name, char *value, t_env	**env);
void		free_data(t_data *data);
void		add_env_to_data(t_data *data, char **env);
void		free_data(t_data *data);
void		init_data(t_data *data);
void		new_missing_prompt(char _errcode);
void		priv_create_node(char *name, char *value, t_data *data);

char		env_exist(char *name, t_data *data);

int			setenvval(char *envname, char *newval, t_env **env);

char		*create_shading(char *normal_prompt, t_rgb s, t_rgb inc);
char		*getenvval(char *envname, t_env *env);

t_env		*env_create_node(const char *var, t_data *data);

/* **************************************************************** */
/*																	*/
/*		  __| \ \  /  __|   __|  |  | __ __| _ _|   _ \   \ |		*/
/*		  _|   >  <   _|   (     |  |    |     |   (   | .  |		*/
/*		 ___|  _/\_\ ___| \___| \__/    _|   ___| \___/ _|\_|		*/
/*																	*/
/* **************************************************************** */

void		do_redirections(t_data *data, t_token *cmdline, int mode);
void		custom_execve(char *path, t_token *cmdline, t_data *data);
void		waitchildren(t_data *data);
void		dup2_stdin(t_data *data, t_token *cmdline, int fd[2]);
void		dup2_stdout(t_data *data, t_token *cmdline, int fd[2]);
void		open_pipe(t_token *cmdline, int fd[2]);
void		fprint_invalidcmd(t_token *cmdline);
void		save_stdfileno(int fileno_[3]);
void		restore_stdfileno(int fileno_[3]);
void		exec(t_data *data);

char		is_an_execbin(char *path_to_f);
char		is_redirection(t_token *redirection);
char		is_there_redirect(t_token *cmdline);
char		check_exitedchild(t_data *data, int *status);
char		is_there_cmd(t_token *cmdline);
char		is_a_builtin(t_token *cmdline);

int			ft_fork(t_data *data);
int			is_there_subshells(t_token *cmdline, t_data *data);
int			exec_builtins(char blt_val, t_data *data, t_token *cmdline);

t_e_type	tok_next_type(t_token *last);

char		*take_absocmd(char	*path_to_file);
char		*take_dir(char *path_to_file);
char		*catch_execbin(t_token *cmdline);
char		*getcmdpath(t_token **cmdline, t_data *data);

char		**convert_env(t_env *env);
char		**tok_to_strs(t_token *cmdline);

t_token		*tok_skip_subshell(t_token *cmdline);
t_token		*tok_next_redirect(t_token *cmdline);
t_token		*tok_next_cmd(t_token *last);
t_token		*tok_next_sep(t_token *last);

/* ******************************************************** */
/*															*/
/*		  _ )  |  | _ _|  |  __ __| _ _|   \ |   __|		*/
/*		  _ \  |  |   |   |     |     |   .  | \__ \		*/
/*		 ___/ \__/  ___| ____| _|   ___| _|\_| ____/		*/
/*															*/
/* ******************************************************** */

void		show_dir_contents(char *filename, char *ref, t_data *data);

int			export_args(char **args, t_env **head);
int			ft_cd(char **arguments, t_data *data);
int			ft_echo(char **arguments, t_data *data);
int			ft_env(char **args, t_data *data);
int			ft_exit(char **av, t_data *data);
int			ft_export(char **args, t_data *data);
int			ft_ls(char **args, t_data *data);
int			ft_pwd(char **args, t_data *data);
int			ft_unset(char **arguments, t_data *data);
int			hdel(char **arguments, t_data *data);

/* **************************************************** */
/*														*/
/*		  |  | _ _|   __| __ __| _ \  _ \ \ \  /		*/
/*		  __ |   |  \__ \    |  (   |   /  \  /			*/
/*		 _| _| ___| ____/   _| \___/ _|_\   _|			*/
/*														*/
/* **************************************************** */

void		close_hfile(t_data *data);
void		add_to_history(char *line, t_data *data);

int			open_hfile(t_data *data);

char		*up_history(char *line, t_data *data);
char		*get_history_fpath(t_data *data);
char		*search_in_history(char *line, t_data *data);
void		free_history_info(t_data *data);
void		new_history_info_node(t_data *data, t_history **history, char *gnl);
char		*down_history(char *line, t_data *data);

/* **************************************************** */
/*														*/
/*  		_ \  \    _ \   __| _ _|   \ |   __|		*/
/*  		__/ _ \     / \__ \   |   .  |  (_ |		*/
/*		   _| _/  _\ _|_\ ____/ ___| _|\_| \___|		*/
/*														*/
/* **************************************************** */

void		inspect_all_files(t_data *data, char *dir,
			t_token **newtok, t_joker joker);
void		tok_set_null_to_arg(t_token **root);
void		reset_commandtype(t_token **root);
void		print_env(t_env *env);
void		take_commandline(const char *line, t_data *data);
void		free_tokens(t_token **root);
void		place_envvars(char ***splitted, t_data *data);
//void		apply_wildcards(char ***splitted);
void		jokeroverride(t_token **root, t_data *data);
void		tokenise_joker(t_token **root);
void		separate_operands(char ***splitted);
void		check_quote_status(char c, char *opened_status);
void		check_e_type(t_token **second, const char *word, int i);
void		remquotes(char **new, char *src);
void		remquotes_joker(char **new, char *src);
void		review_tokenid(t_token **tokens);
void		detect_redirect_type(t_token **tok);
void		check_potential_errors(char **splitted, t_data *data);
void		delete_token(t_token **root, t_token **to_del);
void		insert_token(t_token **after_it, t_token *new);

char		check_parse_error(char ***splitted, t_data *data);
char		is_operand(char c[3]);
char		is_sep(char c);
char		is_sep_toktype(t_token tok);
char		is_missing_septoktype(int _errcode);
char		handle_generic_error(char ***splitted, t_data *data);

size_t		cwlen_joker(const char *word);

char		*return_missing_chars(char _errcode);
void		remove_useless_quotes(t_token **root, t_data *data);

t_token		*check_tokens_error(t_token *tokens, t_data *data);
t_token		*new_token(char *value);
t_token		*ret_last_token(t_token *tokens);

char		**ft_split_quotes(const char *s, char (*_is_sep)(char c), t_data *data);

/* **************************************************** */
/*														*/
/*		 __ __| __|  _ \   \  |   __|    \    _ \		*/
/*		    |   _|     /  |\/ |  (      _ \   __/		*/
/*		   _|  ___| _|_\ _|  _| \___| _/  _\ _|			*/
/*														*/
/* **************************************************** */

void		resize_line_buffer(t_data *data);
void		tab_clear(t_data *data);
void		tab_reset(t_data *data, int clear);
void		enter_tab_mode(t_data *data);
void		tab_select(t_data *data, char shortcut);
void		print_files(t_data *data);
void		kill_term(t_data *data);
void		term_init(t_data *data, char **env) __attribute__((cold));
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
void		write_stored_dont_move(t_term *term, int at, char *mem, int cnt)
			__attribute__((hot));
void		write_stored_move(t_term *term, int at, char *mem, int cnt)
			__attribute__((hot));
void		print_char(t_data *data, int c)
			__attribute__((hot));
void		key_backspace(t_data *data) __attribute__((hot));
void		key_delete(t_data *data) __attribute__((hot));
void		key_tab(t_data *data) __attribute__((hot));
void		free_term(t_data *data) __attribute__((cold));

int			key_up(t_data *data) __attribute__((hot));
int			key_down(t_data *data) __attribute__((hot));
int			key_right(t_data *data) __attribute__((hot));
int			key_left(t_data *data) __attribute__((hot));
int			ft_read(int fd, char *buf, int size, t_data *data);

char		*fetch_dir_name(char *path);
char		*fetch_file_name(char *path);
char		*ft_readline(char *prompt, t_data *data) __attribute__((hot));

/*		DEBUG		*/

void		show_token(t_token *tok);

#endif
