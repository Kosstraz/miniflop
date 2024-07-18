/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:19:42 by bama              #+#    #+#             */
/*   Updated: 2024/07/18 16:54:31 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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