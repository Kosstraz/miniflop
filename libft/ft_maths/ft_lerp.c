/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:34:56 by ymanchon          #+#    #+#             */
/*   Updated: 2024/07/08 19:43:33 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_lerp(int a, int b, float t)
{
	return (a + (b - a) * t);
}

float	ft_lerpf(float a, float b, float t)
{
	return (a + (b - a) * t);
}

double	ft_lerpd(double a, double b, float t)
{
	return (a + (b - a) * t);
}
