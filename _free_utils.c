/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _free_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:12:15 by toshi             #+#    #+#             */
/*   Updated: 2024/01/17 17:18:59 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	tkn_free(t_token *tkn)
{
	free(tkn->val);
	free(tkn);
}

void	tkn_free_lst(t_token *head)
{
	t_token *next_ptr;
	t_token *ptr;

	if (head == NULL)
		return ;
	ptr = head;
	next_ptr = head->next;
	while(next_ptr != NULL)
	{
		tkn_free(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	tkn_free(ptr);
}

void	tnode_free(t_tree_node 	*tnode)
{
	tkn_free_lst(tnode->init_data.cmd_tokens);
	if (tnode->init_data.infile_tokens)
		tkn_free_lst(tnode->init_data.infile_tokens);
	if (tnode->init_data.outfile_tokens)
		tkn_free_lst(tnode->init_data.outfile_tokens);
	free(tnode);
}

void	tnode_free_lst(t_tree_node *head)
{
	t_tree_node *next_ptr;
	t_tree_node *ptr;

	if (head == NULL)
		return;
	ptr = head;
	next_ptr = head->right;
	while(next_ptr != NULL)
	{
		tnode_free(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->right;
	}
	tnode_free(ptr);
}