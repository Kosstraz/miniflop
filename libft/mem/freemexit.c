/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:05:31 by bama              #+#    #+#             */
/*   Updated: 2024/07/07 19:21:31 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	freemexit(int errcode, int ac, ...)
{
	va_list	args;

	va_start(args, ac);
	while (ac--)
		free(va_arg(args, void *));
	va_end(args);
	exit(errcode);
}
