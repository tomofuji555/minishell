/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:10:35 by toshi             #+#    #+#             */
/*   Updated: 2024/01/17 16:13:28 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_tree_node	*tnode_find_last_right(t_tree_node *head)
{
	t_tree_node *ptr;

	ptr = head;
	while(ptr->right != NULL)
		ptr = ptr->right;
	return (ptr);
}

void	tnode_add_last_right(t_tree_node **head, t_tree_node *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tnode_find_last_right(*head)->right = new;
}