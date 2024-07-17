/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:33:43 by bama              #+#    #+#             */
/*   Updated: 2024/07/18 00:50:26 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\e[1m\e[35mMINIFLOP $> \e[0m"
# define PROMPT_SIZE 26

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>

typedef enum e_type
{
	Pipe,
	And,
	Or,
	Command,
	Redirect,
	Argument
}	t_e_type;

typedef struct s_token
{
	enum e_type		type;
	const char		*value;
	struct s_token	*next;
}	t_token;

/*		MINISHELL		*/

char	*get_next_line(int fd);
void	minishell(void);
void	new_prompt(void);

/*		PARSING			*/

void	read_prompt(void);

#endif