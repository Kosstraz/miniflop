/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 23:41:11 by bama              #+#    #+#             */
/*   Updated: 2024/07/20 15:59:25 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1 option valid
// 0 option not valid
char	ft_is_option(const char *word)
{
	if (!ft_strncmp(word, "-n", 2))
	{
		word += 2;
		while (*word)
		{
			if (*word != 'n')
				return (0);
			word++;
		}
		return (1);
	}
	return (0);
}

int	ft_echo(char **arguments)
{
	size_t	i;
	char	option;
	char	args;

	i = 0;
	args = 0;
	option = 0;
	while (arguments[i])
	{
		if (!ft_is_option(arguments[i]) || args)
		{
			args = 1;
			write(1, arguments[i], ft_strlen(arguments[i]));
			if (arguments[i + 1])
				write(1, " ", 1);
		}
		else if (!args)
			option = 1;
		i++;
	}
	if (!option)
		write(1, "\n", 1);
	return (0);
}
