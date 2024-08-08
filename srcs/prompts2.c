/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:08:30 by bama              #+#    #+#             */
/*   Updated: 2024/08/08 22:08:48 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char	*prompt_add_retcmd(char *prompt, t_data *data)
{
	prompt = ft_strdup("[");
	prompt = strlljoin(prompt, getenvval("?", data->env));
	prompt = strljoin(prompt, "] - ");
	return (prompt);
}
