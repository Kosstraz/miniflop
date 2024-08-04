/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:05:53 by cachetra          #+#    #+#             */
/*   Updated: 2024/08/04 17:13:49 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
	GENERIC
*/
# define TRUE	1
# define FALSE	0

/*
	TEXT ERROR
*/
# define UNKNOW_CMD_PRINTF1 "\e[31m\ninvalid command : not found \
\"\e[1m"
# define UNKNOW_CMD_PRINTF1_SIZE 39

# define UNKNOW_CMD_PRINTF2 "\e[0;31m\"\n\e[0m"
# define UNKNOW_CMD_PRINTF2_SIZE 13

# define PARSE_ERROR_T "\e[31m\nparse error :/\n\e[0m"
# define PARSE_ERROR_SIZE 25

# define COMMAND_IS_DIR_ERROR "\e[31m\ncommand is a directory :/\n\e[0m"
# define COMMAND_IS_DIR_ERROR_SIZE 36

# define TOO_MANY_ARGS_ERROR "\e[31m\nexit(int) : too many arguments\n\e[0m"
# define TOO_MANY_ARGS_ERROR_SIZE 41

# define ENV_ARGS_ERROR "\e[31m\nenv : too many arguments\n\e[0m"
# define PWD_ARGS_ERROR "\e[31m\npwd : too many arguments\n\e[0m"
# define ARGS_ERROR_SIZE 35

# define NO_MATCH_FOUND_ERROR "\e[31m\nno match found \
with wildcard '%s' :O\n\e[0m"

# define SQUOTE_ERROR "\e[31m\nparse error caused by an non-closed \
\e[1msquote\e[0m\n"
# define DQUOTE_ERROR "\e[31m\nparse error caused by an non-closed \
\e[1mdquote\e[0m\n"
# define PIPE_ERROR "\e[31m\nparse error caused by an incomplete \
\e[1mpipe\e[0m\n"
# define AND_ERROR "\e[31m\nparse error caused by an incomplete \
\e[1mand\e[0m\n"
# define OR_ERROR "\e[31m\nparse error caused by an incomplete \
\e[1mor\e[0m\n"
# define SUBSHELL_ERROR "\e[31m\nparse error caused by an non-closed \
\e[1msubshell\e[0m\n"

/*
	INT ERROR
*/
# define __ERROR__			-1
# define BAD_MALLOC 		-2
# define SPLIT_ERROR 		-3
# define ENVVAR_NOTFOUND	-4

# define SQUOTE_MISSING		-10
# define DQUOTE_MISSING		-11
# define SUBSHELL_MISSING	-12
# define INCOMPLETE_PIPE	-13
# define INCOMPLETE_AND		-14
# define INCOMPLETE_OR		-15

/*
	bash --posix ERROR
*/
# define CMD_UNKNOW		127
# define PARSE_ERROR	1
# define ERROR			1
# define SUCCESS		0

#endif