/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:33:43 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 20:08:29 by bama             ###   ########.fr       */
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

# define SQUOTE_PROMPT "\e[1mmsquote >>> \e[0m"
# define SQUOTE_PROMPT_SIZE 26

# define DQUOTE_PROMPT "\e[1mmdquote >>> \e[0m"
# define DQUOTE_PROMPT_SIZE 26

# define EXIT_TEXT "\e[31m\nexit\n\e[0m"
# define EXIT_TEXT_SIZE 15

# ifndef ARG_MAX
#  define ARG_MAX 2087151
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include "err.h"
# include "libft.h"

typedef enum e_type
{
	Null,
	Pipe,
	And,
	Or,
	Command,
	Argument,
	Redirect,
	Infile,
	Outfile
}	t_e_type;

typedef struct s_token
{
	enum e_type		type;
	const char		*value;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	t_token	*tokens;
	int		errcode;
}	t_data;

/*		BUILTINS		*/

int		ft_cd(char **arguments);
int		ft_echo(char **arguments);

/*		MINISHELL		*/

void	minishell(char **env);
void	new_prompt(void);
void	free_datas(t_data *datas);
void	signals_handling(int signum);;

/*		PARSING			*/

char	**remove_useless_quotes(char **splitted);
char	**ft_split_quotes(const char *s, char sep);
void	take_commandline(const char *line, t_data *datas);
t_token	*new_token(char *value);
void	free_tokens(t_token **root);
void	place_envvars(char ***splitted);
void	place_wildcards(char ***splitted);
void	separate_operands(char ***splitted);
void	check_quote_status(char c, char *opened_status);
char	is_operand(char c[2]);
char	is_sep(char c);

/*		DEBUG		*/

void	show_token(t_token *tok);

#endif