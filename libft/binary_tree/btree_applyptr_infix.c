/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_applyptr_infix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:33:25 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/18 11:36:49 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_applyptr_infix(t_btree **root, void (*applyf)(T_BTREE *))
{
	if (root && *root)
	{
		btree_applyptr_infix((*root)->left, applyf);
		applyf(&(*root)->item);
		btree_applyptr_infix((*root)->right, applyf);
	}
}
