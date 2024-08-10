/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_addr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:57:14 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/13 12:42:52 by ymanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	swap_addr(void **a, void **b)
{
	unsigned long	al;
	unsigned long	bl;

	al = (unsigned long long)(*a);
	bl = (unsigned long long)(*b);
	*a = (void *)bl;
	*b = (void *)al;
}
