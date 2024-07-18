/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:24:37 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/18 11:36:42 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*btree_create_node(T_BTREE item)
{
	t_btree	*ret;

	ret = (t_btree *)malloc(sizeof(t_btree));
	if (!ret)
		return (NULL);
	ret->left = NULL;
	ret->right = NULL;
	ret->item = item;
	return (ret);
}
