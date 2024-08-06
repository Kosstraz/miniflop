/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:10:12 by bama              #+#    #+#             */
/*   Updated: 2024/08/06 23:07:44 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_notdir(char *path);

static void	change_pwdenvval(char *old_pwd, t_data *data)
{
	setenvval("OLDPWD", old_pwd, &data->env);
	setenvval("PWD", getcwd(NULL, 0), &data->env);
}

static int	ft_cd_home(t_data *data)
{
	char	*oldpwd;
	char	*path;
	char	*user;
	int		log;

	oldpwd = getenvval("PWD", data->env);
	user = getenvval("USER", data->env);
	path = ft_strjoin("/home/", user);
	free(user);
	log = chdir(path);
	if (log != 0)
	{
		free(path);
		free(oldpwd);
		data->ret_cmd = -log;
		return (-log);
	}
	free(path);
	change_pwdenvval(oldpwd, data);
	return (-log);
}

static int	ft_cd_at(t_data *data)
{
	char	*oldpwd;
	char	*path;
	int		log;

	if (!env_exist(CWD_AT_NAME, data))
	{
		write(2, CD_NO_OVERLOAD, ft_strlen(CD_NO_OVERLOAD));
		return (1);
	}
	oldpwd = getenvval("PWD", data->env);
	path = getenvval(CWD_AT_NAME, data->env);
	log = chdir(path);
	if (log != 0)
	{
		free(path);
		free(oldpwd);
		data->ret_cmd = -log;
		return (-log);
	}
	change_pwdenvval(oldpwd, data);
	printf("%s%s@ : %s%s\n", ITALIC, OPACITY, path, RESET);
	free(path);
	return (-log);
}

static int	ft_cd_edgecase(char **arguments, t_data *data)
{
	char	*oldpwd;
	char	*path;
	int		log;

	if (!ft_strcmp(arguments[1], "-"))
	{
		oldpwd = getenvval("PWD", data->env);
		path = getenvval("OLDPWD", data->env);
		log = chdir(path);
		if (log != 0)
		{
			free(path);
			free(oldpwd);
			return (data->ret_cmd = log, log);
		}
		change_pwdenvval(oldpwd, data);
		printf("%s%s%s --> %s%s\n", ITALIC, OPACITY, oldpwd, path, RESET);
		free(path);
		return (-log);
	}
	else if (!ft_strcmp(arguments[1], "@"))
		return (ft_cd_at(data));
	else if (!ft_strcmp(arguments[1], "~"))
		return (ft_cd_home(data));
	return (-1);
}

int	ft_cd(char **arguments, t_data *data)
{
	char	*oldpwd;
	int		log;

	if (!arguments || !arguments[1])
		return (ft_cd_home(data));
	else if (arguments[1] && arguments[2])
	{
		write(2, CD_ARGS_ERROR, ARGS_ERROR_SIZE);
		return (ERROR);
	}
	log = ft_cd_edgecase(arguments, data);
	if (log >= 0)
		return (log);
	oldpwd = getenvval("PWD", data->env);
	log = chdir(arguments[1]);
	if (log != 0)
	{
		ft_cd_notdir(arguments[1]);
		return (free(oldpwd), -log);
	}
	change_pwdenvval(oldpwd, data);
	data->ret_cmd = -log;
	return (-log);
}
