/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:50:27 by bama              #+#    #+#             */
/*   Updated: 2024/07/09 15:17:06 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

float	ft_absf(float a)
{
	if (a < 0.0f)
		return (-a);
	return (a);
}

double	ft_absd(double a)
{
	if (a < 0.0)
		return (-a);
	return (a);
}
