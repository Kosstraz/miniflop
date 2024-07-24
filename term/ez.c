/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ez.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cachetra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:25:42 by cachetra          #+#    #+#             */
/*   Updated: 2024/07/23 18:45:40 by cachetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs

*/

void	initialise(t_term *term)
{
	int		x;

	term->termtype = getenv("TERM");
	x = tgetent(NULL, term->termtype);
	ft_printf("test: %s\n%d\n", term->termtype, x);
}

void	terminal(t_data *data)
{
	initialise(&data->term);
}
