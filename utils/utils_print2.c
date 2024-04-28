/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:30 by toshi             #+#    #+#             */
/*   Updated: 2024/04/28 15:05:43 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_init_data(t_tree_node *tree_node)
{
	printf("<<init_data>>\n");
	if (tree_node->init_data.cmd_tokens != NULL)
	{
		printf("<cmd>\n");
		print_token_list(tree_node->init_data.cmd_tokens);
	}
	if (tree_node->init_data.infile_tokens != NULL)
	{
		printf("<infile>\n");
		print_token_list(tree_node->init_data.infile_tokens);
	}
	if (tree_node->init_data.outfile_tokens != NULL)
	{
		printf("<outfile>\n");
		print_token_list(tree_node->init_data.outfile_tokens);
	}
}

void	print_adv_data(t_tree_node	*tree_node)
{
	printf("<<adv_data>>\n");
	if (tree_node->adv_data.cmd_args)
	{
		printf("<cmd>\n");
		print_cmd_args(tree_node->adv_data.cmd_args);
	}
	if (tree_node->adv_data.infile_paths)
	{
		printf("<infile>\n");
		print_redir_list(tree_node->adv_data.infile_paths);
	}
	if (tree_node->adv_data.outfile_paths)
	{
		printf("<outfile>\n");
		print_redir_list(tree_node->adv_data.outfile_paths);
	}
}

/// @brief 木構造がちゃんと構成されているか、prevがちゃんとつながっているかのテスト
void	print_tree(t_tree_node *root)
{
	t_tree_node	*ptr;

	ptr = root;
	while (ptr->left != NULL)
	{
		ptr = ptr->left;
	}
	while (ptr != NULL)
	{
		print_init_data(ptr);
		if (ptr->right != NULL)
			print_init_data(ptr->right);
		ptr = ptr->prev;
	}
}
