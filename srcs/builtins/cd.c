/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:10:12 by bama              #+#    #+#             */
/*   Updated: 2024/07/30 15:23:36 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **arguments, t_data *data)
{
	char	*pwd;
	char	*oldpwd;
	int		log;

	oldpwd = getenvval("PWD", data->env);
	setenvval("OLDPWD", oldpwd, &data->env);
	log = chdir(arguments[1]);
	pwd = getcwd(NULL, 0);
	setenvval("PWD", pwd, &data->env);
	closedir(data->dir);
	data->dir = opendir(".");
	data->ret_cmd = -log;
	return (-log);
}
