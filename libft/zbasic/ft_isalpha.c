/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:09:58 by ymanchon          #+#    #+#             */
/*   Updated: 2024/05/23 13:37:57 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

static int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
