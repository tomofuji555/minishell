/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:30 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 17:39:31 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_init_data(t_tree_node *ptr)
{
	printf("<<init_data>>\n");
	if (ptr->init_data.cmd_tokens != NULL)
	{
		printf("<cmd>\n");
		print_token_list(ptr->init_data.cmd_tokens);
	}
	if (ptr->init_data.infile_tokens != NULL)
	{
		printf("<infile>\n");
		print_token_list(ptr->init_data.infile_tokens);
	}
	if (ptr->init_data.outfile_tokens != NULL)
	{
		printf("<outfile>\n");
		print_token_list(ptr->init_data.outfile_tokens);
	}
}

void	print_adv_data(t_tree_node	*ptr)
{
	printf("<<adv_data>>\n");
	if (ptr->adv_data.cmd_args)
	{
		printf("<cmd>\n");
		print_cmd_args(ptr->adv_data.cmd_args);
	}
	if (ptr->adv_data.infile_paths)
	{
		printf("<infile>\n");
		print_redir_list(ptr->adv_data.infile_paths);
	}
	if (ptr->adv_data.outfile_paths)
	{
		printf("<outfile>\n");
		print_redir_list(ptr->adv_data.outfile_paths);
	}
}

void	print_init_of_tnode_list(t_tree_node *tnode_ptr)
{
	size_t	i;

	i = 0;
	while (tnode_ptr != NULL)
	{
		printf("--------node_No==%zd--------\n", i++);
		print_init_data(tnode_ptr);
		tnode_ptr = tnode_ptr->right;
	}
}

void	print_adv_of_tnode_list(t_tree_node *tnode_ptr)
{
	size_t	i;

	i = 0;
	while (tnode_ptr != NULL)
	{
		printf("--------node_No==%zd--------\n", i++);
		if (is_cmd_node(tnode_ptr))
			print_adv_data(tnode_ptr);
		else
		{
			printf("<<pipe>>\n");
		}
		tnode_ptr = tnode_ptr->right;
	}
}

/// @brief 木構造がちゃんと構成されているか、prevがちゃんとつながっているかのテスト
void	print_tree(t_tree_node *root)
{
	t_tree_node	*ptr;
	size_t		i;

	ptr = root;
	while (ptr->left != NULL)
	{
		if (ptr->right != NULL)
			print_init_data(ptr->right);
		ptr = ptr->left;
	}
	wc("left");
	print_init_data(ptr);
	while (ptr != NULL)
	{
		if (ptr->right != NULL)
		{
			wc("right");
			print_init_data(ptr->right);
		}
		ptr = ptr->prev;
	}
}
