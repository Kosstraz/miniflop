/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:58:29 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/18 11:36:36 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*btree_infix_node(t_btree *root)
{
	if (!root)
		return (NULL);
	while (root->left)
		root = root->left;
	return (root);
}

T_BTREE	btree_search_item_recu(t_btree *root, const T_BTREE data_ref,
		T_BTREE *nullable, int (*cmpf)(T_BTREE, T_BTREE))
{
	if (!root)
		return (*nullable);
	btree_search_item_recu(root->left, data_ref, nullable, cmpf);
	if (cmpf(data_ref, root->item) == 0)
	{
		*nullable = data_ref;
		return (*nullable);
	}
	btree_search_item_recu(root->right, data_ref, nullable, cmpf);
	return (*nullable);
}

T_BTREE	btree_search_item(t_btree *root, const T_BTREE data_ref,
		int (*cmpf)(T_BTREE, T_BTREE))
{
	T_BTREE	ret;

	ret = 0;
	return (btree_search_item_recu(root, data_ref, &ret, cmpf));
}
