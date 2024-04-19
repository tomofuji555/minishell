/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:02:01 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 00:19:57 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_init_data(t_tree_node *ptr)
{
	if (ptr->init_data.cmd_tokens)
		free_token_list(ptr->init_data.cmd_tokens);
	if (ptr->init_data.infile_tokens)
		free_token_list(ptr->init_data.infile_tokens);
	if (ptr->init_data.infile_tokens)
		free_token_list(ptr->init_data.outfile_tokens);
}

void	free_adv_data(t_tree_node 	*tnode)
{
	if (tnode->adv_data.cmd_args)
		free_multi_strs(tnode->adv_data.cmd_args);
	if (tnode->adv_data.infile_paths)
		free_redir_list(tnode->adv_data.infile_paths);
	if (tnode->adv_data.outfile_paths)
		free_redir_list(tnode->adv_data.outfile_paths);
}

void	free_tree_node(t_tree_node *ptr)
{
	free_init_data(ptr);
	free_adv_data(ptr);
	free(ptr);
}

void	free_tnode_list(t_tree_node *head)
{
	t_tree_node *next_ptr;
	t_tree_node *ptr;

	if (head == NULL)
		return;
	ptr = head;
	next_ptr = head->right;
	while(next_ptr != NULL)
	{
		free_tree_node(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->right;
	}
	free_tree_node(ptr);
}

void	free_tree(t_tree_node *root)
{
	t_tree_node	*ptr;	
	t_tree_node	*prev;

	ptr = root;
	while (ptr->left != NULL)
		ptr = ptr->left;
	while (ptr != NULL)
	{
		prev = ptr->prev;
		if (ptr->right != NULL)
			free_tree_node(ptr->right);
		free_tree_node(ptr);
		ptr = prev;
	}
}