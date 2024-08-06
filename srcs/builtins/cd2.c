/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:57:28 by bama              #+#    #+#             */
/*   Updated: 2024/08/06 22:59:12 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Seulement pour l'erreur "cd : X is not a directory"
void	ft_cd_notdir(char *arg1)
{
	write(2, CD_INVALID_ARG1, ft_strlen(CD_INVALID_ARG1));
	write(2, arg1, ft_strlen(arg1));
	write(2, CD_INVALID_ARG2, ft_strlen(CD_INVALID_ARG2));
}
