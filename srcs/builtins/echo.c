/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 23:41:11 by bama              #+#    #+#             */
/*   Updated: 2024/07/20 00:06:23 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **arguments)
{
	size_t	i;
	char	option;

	i = 0;
	option = 0;
	while (arguments[i])
	{
		if (ft_strcmp(arguments[i], "-n"))
		{
			write(1, arguments[i], ft_strlen(arguments[i]));
			if (arguments[i + 1] && ft_strcmp(arguments[i + 1], "-n"))
				write(1, " ", 1);
		}
		else
			option = 1;
		i++;
	}
	if (!option)
		write(1, "\n", 1);
	return (0);
}
