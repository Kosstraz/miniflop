/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:10:12 by bama              #+#    #+#             */
/*   Updated: 2024/11/17 16:33:18 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_notdir(char *path);
int		ft_cd_back(t_data *data);
char	*replace_tild(char *old, t_data *data);

void	change_pwdenvval(char *old_pwd, t_data *data)
{
	setenvval("OLDPWD", old_pwd, &data->env);
	setenvval("PWD", getcwd(NULL, 0), &data->env);
}

int	ft_cd_home(t_data *data)
{
	char	*oldpwd;
	char	*path;
	char	*user;
	int		log;

	oldpwd = getenvval("PWD", data->env);
	user = getenvval("USER", data->env);
	path = ft_strdup("/home/");
	path = strlljoin(path, user);
	log = chdir(path);
	if (log != 0)
	{
		free(path);
		free(oldpwd);
		data->ret_cmd = -log;
		return (-log);
	}
	printf("%s%s~ : %s%s\n", ITALIC, OPACITY, path, RESET);
	free(path);
	change_pwdenvval(oldpwd, data);
	return (-log);
}

int	ft_cd_at(t_data *data)
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
	if (path[0] == '~')
		path = replace_tild(path, data);
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
	if (!ft_strcmp(arguments[1], "-"))
		return (ft_cd_back(data));
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
	log = ft_cd_specialmove(arguments[1], data);
	log = chdir(&arguments[1][log]);
	if (log != 0)
	{
		ft_cd_notdir(arguments[1]);
		return (free(oldpwd), -log);
	}
	change_pwdenvval(oldpwd, data);
	data->ret_cmd = -log;
	return (-log);
}
