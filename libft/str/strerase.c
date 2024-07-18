/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strerase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:05:04 by bama              #+#    #+#             */
/*   Updated: 2024/06/20 13:25:37 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	strerase(char **buffer, const char *insert, int at, int len)
{
	int	i;

	i = 0;
	while (insert[i] && i < len)
		(*buffer)[at++] = insert[i++];
	while (i++ < len)
		(*buffer)[at++] = 0;
}
