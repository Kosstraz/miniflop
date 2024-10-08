/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 22:01:38 by bama              #+#    #+#             */
/*   Updated: 2024/08/09 01:58:19 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

char	*va_strjoin(size_t count, ...)
{
	char	*ret;
	size_t	i;
	va_list	va;

	va_start(va, count);
	i = 0;
	if (count == 0)
		return (NULL);
	ret = ft_strdup(va_arg(va, char *));
	while (i++ < count)
		ret = strljoin(ret, va_arg(va, char *));
	va_end(va);
	return (ret);
}

char	*va_strljoin(size_t count, ...)
{
	char	*ret;
	char	*arg;
	size_t	i;
	va_list	va;

	va_start(va, count);
	if (count == 0)
		return (NULL);
	ret = ft_strldup(va_arg(va, char *));
	i = 0;
	count--;
	arg = va_arg(va, char *);
	while (arg && i++ < count)
	{
		ret = strlljoin(ret, arg);
		arg = va_arg(va, char *);
	}
	va_end(va);
	return (ret);
}
