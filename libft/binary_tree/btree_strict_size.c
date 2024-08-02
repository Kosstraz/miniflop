/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_strict_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bama <bama@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:31:53 by ymanchon          #+#    #+#             */
/*   Updated: 2024/06/18 11:36:19 by bama             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	btree_strictleft_size(t_btree *tree)
{
	int	i;

	i = -1;
	while (tree)
	{
		tree = tree->left;
		i++;
	}
	return (i);
}

int	btree_strictright_size(t_btree *tree)
{
	int	i;

	i = -1;
	while (tree)
	{
		tree = tree->right;
		i++;
	}
	return (i);
}
