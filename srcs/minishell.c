/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:41:31 by bama              #+#    #+#             */
/*   Updated: 2024/07/18 00:25:00 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline void	new_prompt(void)
{
	write(1, PROMPT, PROMPT_SIZE);
}

void	minishell(void)
{
	new_prompt();
	read_prompt();
}
