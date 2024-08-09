/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 02:00:39 by bama              #+#    #+#             */
/*   Updated: 2024/08/09 17:48:23 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_quotes(char c, char *quote_type)
{
	if (c == '\'')
		*quote_type = 1;
	else if (c == '"')
		*quote_type = 2;
	return (*quote_type);
}

static size_t	strtruncquotes_countword(char *str, char t)
{
	size_t	i;
	size_t	len;
	char	c;
	char	quote_status;

	if (!str)
		return (0);
	quote_status = 0;
	len = 0;
	i = 0;
	while (str[i])
	{
		c = str[i];
		check_quotes(c, &quote_status);
		if (quote_status || (c == '\'' || c == '"'))
			len++;
		else if ((i == 0 || c != t) || (i != 0 && str[i - 1] != ' ' && c == t))
			len++;
		i++;
	}
	return (len);
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
	size_t	j;
	size_t	size;
	char	c;
	char	quote_status;

	i = 0;
	j = 0;
	quote_status = 0;
	size = strtruncquotes_countword(str, t);
	trunc = (char *)malloc(sizeof(char) * (size + 1));
	if (!trunc)
		return (NULL);
	while (str[i])
	{
		c = str[i];
		check_quotes(c, &quote_status);
		if (quote_status || (c == '\'' || c == '"'))
			trunc[j++] = str[i];
		else if ((i == 0 || c != t) || (i != 0 && str[i - 1] != t && c == t))
			trunc[j++] = str[i];
		i++;
	}
	trunc[j] = 0;
	return (trunc);
}
