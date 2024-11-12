/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:05:53 by cachetra          #+#    #+#             */
/*   Updated: 2024/11/12 16:29:19 by ymanchon         ###   ########.fr       */
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
# define JOKER_ERROR "\n%sjoker : \"%s%s%s%s%s\" : no match found%s\n"

# define UNKNOW_CMD_PRINTF1 "\e[1m\ninvalid command : not found \
\""
# define UNKNOW_CMD_PRINTF1_SIZE 35

# define UNKNOW_CMD_PRINTF2 "\"\n\e[0m"
# define UNKNOW_CMD_PRINTF2_SIZE 7

# define INVALIDFILE_PRINTF1 "\e[1m\ninvalid file name : can not open \
\""
# define INVALIDFILE_PRINTF2 "\"\n\e[0m"

# define PARSE_ERROR_T "\e[31m\nparse error :/\n\e[0m"
# define PARSE_ERROR_SIZE 25

# define COMMAND_IS_DIR_ERROR "\e[31m\ncommand is a directory :/\n\e[0m"
# define COMMAND_IS_DIR_ERROR_SIZE 36

# define TOO_MANY_ARGS_ERROR "\e[1m\nexit(int) : \
\e[5m\e[31mtoo many arguments\n\e[0m"
# define TOO_MANY_ARGS_ERROR_SIZE 50

# define EXIT_ALNUM "\e[1m\nexit(int) : \
\e[5m\e[31mnumeric argument required\n\e[0m"
# define EXIT_ALNUM_SIZE 57

# define ENV_ARGS_ERROR "\e[1m\nenv : \
\e[5m\e[31mtoo many arguments\n\e[0m"
# define PWD_ARGS_ERROR "\e[1m\npwd : \
\e[5m\e[31mtoo many arguments\n\e[0m"
# define CD_ARGS_ERROR "\e[1m\ncd : \
\e[5m\e[31mtoo many arguments\n\e[0m"
# define ARGS_ERROR_SIZE 43

# define UNSET_NOT_FOUND1 "\e[1m\nunset : \e[4:3m\e[58:2:255:0:0m"
# define UNSET_NOT_FOUND2 "\e[0m\e[1;5;31m env var not found\e[0m\n"

# define CD_INVALID_ARG1 "\e[1m\ncd : \e[4:3m\e[58:2:255:0:0m"
# define CD_INVALID_ARG2 "\e[0m\e[1;5;31m is not a directory\e[0m\n"

# define CD_NO_OVERLOAD "\e[1m\ncd : \
\e[5m\e[31mno overload available\n\e[0m"

# define NO_MATCH_FOUND_ERROR "\e[31m\nno match found \
with wildcard %s%s'%s'%s :O\n\e[0m"

# define HDEL_EXIST "\e[2m\e[3m\e[31mhistory file doesn't exist\n\e[0m"
# define HDEL_ERROR "\e[2m\e[3m\e[31mhistory can not be reset\n\e[0m"
# define HDEL_SUCCESS "\e[2m\e[3mhistory successfully reset\n\e[0m"

# define SQUOTE_ERROR		"\e[1m\nparse error caused by an non-closed \
\e[21m\e[58:2:255:122:0msquote\e[0m\n"
# define DQUOTE_ERROR		"\e[1m\nparse error caused by an non-closed \
\e[21m\e[58:2:255:122:0mdquote\e[0m\n"
# define SUBSHELL_ERROR		"\e[1m\nparse error caused by an non-closed \
\e[21m\e[58:2:255:122:0msubshell\e[0m\n"
# define SUBSHELLI_ERROR	"\e[1m\nparse error caused by a \e[21m\e[58:2:255:122:0m\
missing action\e[0;1m in \
\e[21m\e[58:2:255:122:0msubshell\e[0m\n"
# define SUBSHELLU_ERROR	"\e[1m\nparse error caused by a useless \
\e[21m\e[58:2:255:122:0msubshell like \"()\"\e[0m\n"
# define COMMA_ERROR		"\e[1m\nparse error caused by an incomplete \
\e[21m\e[58:2:255:122:0mcomma\e[0m\n"
# define PIPE_ERROR			"\e[1m\nparse error caused by an incomplete \
\e[21m\e[58:2:255:122:0mpipe\e[0m\n"
# define AND_ERROR			"\e[1m\nparse error caused by an incomplete \
\e[21m\e[58:2:255:122:0mand\e[0m\n"
# define OR_ERROR			"\e[1m\nparse error caused by an incomplete \
\e[21m\e[58:2:255:122:0mor\e[0m\n"

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
# define SUBSHELL_INVALID	-13
# define SUBSHELL_USELESS	-14
# define INCOMPLETE_PIPE	-15
# define INCOMPLETE_AND		-16
# define INCOMPLETE_OR		-17
# define INCOMPLETE_COMMA	-18

/*
	bash --posix ERROR
*/
# define CMD_UNKNOW		127
# define PARSE_ERROR	1
# define ERROR			1
# define SUCCESS		0

#endif