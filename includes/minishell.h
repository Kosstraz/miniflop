/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:33:43 by bama              #+#    #+#             */
/*   Updated: 2024/07/18 18:47:17 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\e[1m\e[35mMINIFLOP $> \e[0m"
# define PROMPT_SIZE 26

# define SQUOTE_PROMPT "\e[1mmsquote >>> \e[0m"
# define SQUOTE_PROMPT_SIZE 26

# define DQUOTE_PROMPT "\e[1mmdquote >>> \e[0m"
# define DQUOTE_PROMPT_SIZE 26

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include "errcode.h"
# include "libft.h"

typedef enum e_type
{
	Null,
	Pipe,
	And,
	Or,
	Command,
	Argument,
	Redirect
}	t_e_type;

typedef struct s_token
{
	enum e_type		type;
	const char		*value;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	int	errcode;
}	t_data;

/*		MINISHELL		*/

char	*get_next_line(int fd);
void	minishell(void);
void	new_prompt(void);

/*		PARSING			*/

char	*remove_useless_quotes(const char *line);
void	show_token(const t_token **tok);
void	take_commandline(const char *line);

/*		SPLIT_QUOTES		*/

char	**ft_split_quotes(const char *s, char sep);

/*		LIST HANDLE		*/

t_token	*ft_toknew(char *value);
t_token	**ft_createtok(size_t size);

#endif