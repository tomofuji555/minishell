/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:02:01 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 17:02:31 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_init_data(t_tree_node *tree_node)
{
	if (tree_node->init_data.cmd_tokens)
		free_token_list(tree_node->init_data.cmd_tokens);
	if (tree_node->init_data.infile_tokens)
		free_token_list(tree_node->init_data.infile_tokens);
	if (tree_node->init_data.outfile_tokens)
		free_token_list(tree_node->init_data.outfile_tokens);
}

void	free_adv_data(t_tree_node *tree_node)
{
	if (tree_node->adv_data.cmd_args)
		free_multi_strs(tree_node->adv_data.cmd_args);
	if (tree_node->adv_data.infile_paths)
		free_redir_list(tree_node->adv_data.infile_paths);
	if (tree_node->adv_data.outfile_paths)
		free_redir_list(tree_node->adv_data.outfile_paths);
}

void	free_tree_node(t_tree_node *tree_node)
{
	free_init_data(tree_node);
	free_adv_data(tree_node);
	free(tree_node);
}

void	free_tnode_list(t_tree_node *head)
{
	t_tree_node	*next_ptr;
	t_tree_node	*ptr;

	if (head == NULL)
		return ;
	ptr = head;
	next_ptr = head->right;
	while (next_ptr != NULL)
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
