/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:57:28 by bama              #+#    #+#             */
/*   Updated: 2024/11/11 18:02:22 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwdenvval(char *old_pwd, t_data *data);

char	*replace_tild(char *old, t_data *data)
{
	char	*ret;
	char	*user;

	user = getenvval("USER", data->env);
	ret = ft_strdup("/home");
	if (user)
		ret = strljoin(ret, "/");
	ret = strlljoin(ret, user);
	ret = strljoin(ret, &old[1]);
	free(old);
	return (ret);
}

static char	*replace_home_by_tild(char *old, t_data *data)
{
	char	*ret;
	char	*tmp;
	char	*user;

	user = getenvval("USER", data->env);
	ret = ft_strdup("/home");
	if (user)
		ret = strljoin(ret, "/");
	ret = strlljoin(ret, user);
	if (ft_strncmp(old, ret, ft_strlen(ret)))
		return (free(ret), old);
	tmp = ret;
	ret = ft_strjoin("~", &old[ft_strlen(ret)]);
	free(tmp);
	free(old);
	return (ret);
}

int	ft_cd_back(t_data *data)
{
	char	*oldpwd;
	char	*path;
	int		log;

	oldpwd = getenvval("PWD", data->env);
	path = getenvval("OLDPWD", data->env);
	if (path[0] == '~')
		path = replace_tild(path, data);
	log = chdir(path);
	if (log != 0)
	{
		free(path);
		free(oldpwd);
		return (data->ret_cmd = log, log);
	}
	oldpwd = replace_home_by_tild(oldpwd, data);
	path = replace_home_by_tild(path, data);
	change_pwdenvval(oldpwd, data);
	printf("%s%s%s %s-->%s%s%s %s%s\n", ITALIC, OPACITY, oldpwd, BOLD, RESET, ITALIC, OPACITY, path, RESET);
	free(path);
	return (-log);
}

// Seulement pour l'erreur "cd : X is not a directory"
void	ft_cd_notdir(char *arg1)
{
	write(2, CD_INVALID_ARG1, ft_strlen(CD_INVALID_ARG1));
	write(2, arg1, ft_strlen(arg1));
	write(2, CD_INVALID_ARG2, ft_strlen(CD_INVALID_ARG2));
}

int	ft_cd_specialmove(char *arg1, t_data *data)
{
	if (!ft_strncmp(arg1, "-/", 2))
	{
		ft_cd_back(data);
		return (2);
	}
	else if (!ft_strncmp(arg1, "@/", 2))
	{
		ft_cd_at(data);
		return (2);
	}
	else if (!ft_strncmp(arg1, "~/", 2))
	{
		ft_cd_home(data);
		return (2);
	}
	return (0);
}
