/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:05:53 by cachetra          #+#    #+#             */
/*   Updated: 2024/07/28 15:23:58 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
	BASIC ERROR
*/
# define PARSE_ERROR "\e[31m\nparse error :/\n\e[0m"
# define PARSE_ERROR_SIZE 25

# define COMMAND_IS_DIR_ERROR "\e[31m\ncommand is a directory :/\n\e[0m"
# define COMMAND_IS_DIR_ERROR_SIZE 36

# define TOO_MANY_ARGS_ERROR "\e[31m\nexit(int) : too many arguments\n\e[0m"
# define TOO_MANY_ARGS_ERROR_SIZE 41

# define NO_MATCH_FOUND_ERROR "\e[31m\nno match found with wildcard '%s' :O\n\e[0m"

/*
	LOCAL ERROR
*/
# define ERROR			-1
# define BAD_MALLOC 	-2
# define SPLIT_ERROR 	-3

# define SQUOTE_MISSING	-10
# define DQUOTE_MISSING	-11
# define PIPE_MISSING	-12
# define AND_MISSING	-13
# define OR_MISSING		-14

/*
	bash --posix ERROR
*/

#endif