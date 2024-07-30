/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:05:53 by cachetra          #+#    #+#             */
/*   Updated: 2024/07/30 14:52:09 by bama             ###   ########.fr       */
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
	BASIC ERROR
*/
# define PARSE_ERROR_T "\e[31m\nparse error :/\n\e[0m"
# define PARSE_ERROR_SIZE 25

# define COMMAND_IS_DIR_ERROR "\e[31m\ncommand is a directory :/\n\e[0m"
# define COMMAND_IS_DIR_ERROR_SIZE 36

# define TOO_MANY_ARGS_ERROR "\e[31m\nexit(int) : too many arguments\n\e[0m"
# define TOO_MANY_ARGS_ERROR_SIZE 41

# define NO_MATCH_FOUND_ERROR "\e[31m\nno match found with wildcard '%s' :O\n\e[0m"

/*
	LOCAL ERROR
*/
# define __ERROR__			-1
# define BAD_MALLOC 		-2
# define SPLIT_ERROR 		-3
# define ENVVAR_NOTFOUND	-4

# define SQUOTE_MISSING		-10
# define DQUOTE_MISSING		-11
# define PIPE_MISSING		-12
# define AND_MISSING		-13
# define OR_MISSING			-14

/*
	bash --posix ERROR
*/
# define CMD_UNKNOW		127
# define PARSE_ERROR	1
# define ERROR			1
# define SUCCESS		0

#endif