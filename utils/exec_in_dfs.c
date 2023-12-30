/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_dfs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:36 by toshi             #+#    #+#             */
/*   Updated: 2023/12/31 00:12:43 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

exec_in_dfs(t_tree_node *tree_root)
{
	// t_tree_node *cur_node;
	t_exec_handler	handler;

	handler.cur_node = tree_root;
	if (handler.cur_node->left != NULL)
		run_exec_in_dfs(handler.cur_node->left);
	if (handler.cur_node->init_arg_data.cmd_tokens != NULL)
		do_exec(handler.cur_node);
	if(handler.cur_node->right != NULL)
		run_exec_in_dfs(handler.cur_node->right);
}




