/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:19:42 by bama              #+#    #+#             */
/*   Updated: 2024/07/21 22:54:22 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

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

/*
	bash --posix ERROR
*/

#endif