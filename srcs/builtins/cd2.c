/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:57:28 by bama              #+#    #+#             */
/*   Updated: 2024/08/09 02:18:09 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwdenvval(char *old_pwd, t_data *data);

char	*replace_tild(char *old, t_data *data)
{
	char	*ret;
	char	*user;

	user = getenvval("USER", data->env);
	ret = ft_strdup("/home/");
	ret = strlljoin(ret, user);
	ret = strljoin(ret, "/");
	ret = strljoin(ret, &old[1]);
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

// Seulement pour l'erreur "cd : X is not a directory"
void	ft_cd_notdir(char *arg1)
{
	write(2, CD_INVALID_ARG1, ft_strlen(CD_INVALID_ARG1));
	write(2, arg1, ft_strlen(arg1));
	write(2, CD_INVALID_ARG2, ft_strlen(CD_INVALID_ARG2));
}
