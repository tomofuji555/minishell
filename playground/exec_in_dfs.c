/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_dfs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:36 by toshi             #+#    #+#             */
/*   Updated: 2024/04/14 12:55:11 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


exec_in_while(t_tree_node *root_node)
{
	t_tree_node *cur_node;

	cur_node = root_node;
	while (cur_node->left != NULL)
		cur_node = cur_node->left;
	do_exec(cur_node); //forkし、ストリームを変え、実行、prev_fd＆last_pidを更新
	while (cur_node != NULL)
	{
		if (cur_node->right != NULL)
			de_exec(cur_node->right->exec_arg_data); //forkし、ストリームを変え、実行、prev_fd＆last_pidを更新
		cur_node = cur_node->prev;
	}
	while(0) //forkしたカウント
	{
		if (pid == wait(&status)) //last_pidとwaitの返り値が同じなら
			printf("最終終了ステータス%d\n", WEXITSTATUS(status));
	}
}
