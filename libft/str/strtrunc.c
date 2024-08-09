/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 02:00:39 by bama              #+#    #+#             */
/*   Updated: 2024/08/09 02:08:43 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strtrunc_countword(char *str, char t)
{
	(void)str;
	(void)t;
	return (0);
}

// Va trunc chaque caractère 't' trouvé
// Si t=' ' et que str="  Bonjour   allo  a " alors -->
// strtrunc(str)=" Bonjour allo a "
// Tout en respectant les caractères 't' dans les squotes ou dquotes
// Contrairement à strtrunc
char	*strtrunc_quotes(char *str, char t)
{
	char	*trunc;
	size_t	i;
	char	quote_status;

	i = 0;
	quote_status = 0;
	trunc = NULL;
	(void)quote_status;
	(void)strtrunc_countword(str, t);
	while (str[i])
	{
		(void)t;
		i++;
	}
	return (trunc);
}
