/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:17 by toshi             #+#    #+#             */
/*   Updated: 2024/01/14 23:07:25 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int change_instream(t_redir *redir_head, int prev_output_fd)
{
	int in_fd;

	if (redir_head)
		change_stream_to_redir(redir_head, STDIN_FILENO);
	else
	{
		if (prev_output_fd != STDIN_FILENO)
		{
			if (dup2(prev_output_fd, STDIN_FILENO) == SYS_FAILURE)
				;//exit
		}
	}
	if (close(prev_output_fd) == SYS_FAILURE)
		;//検討
}

int change_outstream(t_redir *redir_head, int pipe_out_fd)
{
	int out_fd;

	if (redir_head)
		change_stream_to_redir(redir_head, STDOUT_FILENO);
	else
	{
		if (is_last_cmd(handler->cur_node))
		{
			if (dup2(pipe_out_fd, STDOUT_FILENO) == SYS_FAILURE)
				;//exit
		}
	}
	if (close(pipe_out_fd) == SYS_FAILURE)
		;//検討
}


int exec_external_cmd(t_tree_node *tree_node)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == SYS_FAILURE)
		return (1);
	pid = fork();
	if (pid == SYS_FAILURE)
		;//エラー文を吐き、exit
	else if (pid == CHILD)
	{
		//子プロセスで実行
	}
	else
	{
		// 親プロセス側の処理
	}
}

void	do_exec()
{
	if (0) //ビルトインコマンドなら
		exec_builtin_cmd()
	else
		exec_external_cmd()
}


// exec_in_while(t_tree_node *root_node)
// {
// 	t_tree_node *cur_node;

// 	cur_node = root_node;
// 	while (cur_node->left != NULL)
// 		cur_node = cur_node->left;
// 	do_exec(cur_node); //forkし、ストリームを変え、実行、prev_fd＆last_pidを更新
// 	while (cur_node != NULL)
// 	{
// 		if (cur_node->right != NULL)
// 			de_exec(cur_node->right->exec_arg_data); //forkし、ストリームを変え、実行、prev_fd＆last_pidを更新
// 		cur_node = cur_node->prev;
// 	}
// 	while(0) //forkしたカウント
// 	{
// 		if (pid == wait(&status)) //last_pidとwaitの返り値が同じなら
// 			printf("最終終了ステータス%d\n", WEXITSTATUS(status));
// 	}
// }