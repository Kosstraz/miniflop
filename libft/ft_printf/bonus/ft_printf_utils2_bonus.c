/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:33:37 by ymanchon          #+#    #+#             */
/*   Updated: 2024/07/03 13:22:35 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_printf.h"

void	add_flag(t_flags_info *finfo, char c)
{
	if (c == ' ')
		finfo->space = 1;
	if (c == '#')
		finfo->diez = 1;
	if (c == '+')
		finfo->plus = 1;
}

void	init_flag(t_flags_info *finfo)
{
	finfo->diez = 0;
	finfo->plus = 0;
	finfo->space = 0;
	finfo->width = -1;
}
