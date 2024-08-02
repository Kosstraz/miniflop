/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_applyptr_suffix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:34:56 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/18 11:36:47 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_applyptr_suffix(t_btree **root, void (*applyf)(T_BTREE))
{
	if (root && *root)
	{
		btree_applyptr_suffix((*root)->left, applyf);
		btree_applyptr_suffix((*root)->right, applyf);
		applyf(&(*root)->item);
	}
}
