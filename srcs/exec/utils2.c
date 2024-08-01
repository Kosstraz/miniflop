/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:42:00 by bama              #+#    #+#             */
/*   Updated: 2024/08/01 12:45:42 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_stdfileno(int fileno_[3])
{
	fileno_[0] = dup(STDIN_FILENO);
	fileno_[1] = dup(STDOUT_FILENO);
	fileno_[2] = dup(STDERR_FILENO);
}

void	restore_stdfileno(int fileno_[3])
{
	dup2(fileno_[0], STDIN_FILENO);
	dup2(fileno_[1], STDOUT_FILENO);
	dup2(fileno_[2], STDERR_FILENO);
}
