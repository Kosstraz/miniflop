/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:19:42 by bama              #+#    #+#             */
/*   Updated: 2024/07/18 17:21:18 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*			check_quotes(s[*i + 1], &quote_type2);
		//if (quote_type2 && quote_type1 == quote_type2)
		//	return (*old = ++(*i), *i);*/
#ifndef ERRCODE_H
# define ERRCODE_H

# define ERROR			-1
# define BAD_MALLOC 	-2
# define SPLIT_ERROR 	-3

	// Besoin d'attendre une suite dans le prompt, exception
# define SQUOTE_MISSING	-10
# define DQUOTE_MISSING	-11

extern int	errcode;

#endif