/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:17 by toshi             #+#    #+#             */
/*   Updated: 2023/12/31 00:12:18 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execute.h"

int get_last_input_fd(t_redir *first_path_node)
{
	t_redir *ptr;
	int in_fd;

	ptr = first_path_node;
	in_fd = -1;
	while(ptr->next != NULL)
	{
		if (in_fd != -1)
			close(in_fd);
		in_fd = open(ptr->val, O_RDONLY);
		if (in_fd == -1)
			;//error
		ptr = ptr->next;
	}
	return (in_fd);
}

int get_last_output_fd(t_redir *first_path_node)
{
	t_redir *ptr;
	int out_fd;

	ptr = first_path_node;
	out_fd = -1;
	while(ptr->next != NULL)
	{
		if (out_fd != -1)
			close(out_fd);
		if (ptr->kind == REDIR_APPEND_FILE)
			out_fd = open(ptr->val, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		else
			out_fd = open(ptr->val, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		if (out_fd == -1)
			;//error
		ptr = ptr->next;
	}
	return (out_fd);
}

int change_input_fd(t_exec_handler *handler)
{
	int in_fd;

	if (handler->infile_paths)
	{
		in_fd = get_last_input_fd(handler->infile_paths);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		close(handler->prev_pipe_in_fd);
	}
	else
	{
		if (handler->prev_pipe_in_fd != STDIN_FILENO)
			dup2(handler->prev_pipe_in_fd, STDIN_FILENO);
		close(handler->prev_pipe_in_fd);
	}
}

int is_last_cmd(t_tree_node *cur_node)
{
	return (cur_node->prev == NULL || cur_node->prev->prev == NULL);
}

int change_output_fd(t_exec_handler *handler, int pipe_out_fd)
{
	int out_fd;

	if (handler->outfile_paths)
	{
		out_fd = get_last_output_fd(handler->outfile_paths);
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
		close(pipe_out_fd);
	}
	else
	{
		if (is_last_cmd(handler->cur_node))
			dup2(pipe_out_fd, STDOUT_FILENO);
		close(pipe_out_fd);
	}
}

void update_prev_pipe_in_fd(t_exec_handler *handler, int *pipe_fd)
{
	
}


int execute(t_tree_node *tree_node)
{
	int				pipe_fd[2];
	pid_t			pid;

	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		//----------子プロセスで実行----------
		printf("子プロセス\n");
	}
	else
	{
		close(pipe_fd[OUT]);
		if (handler->prev_pipe_in_fd != STDIN_FILENO)
			close(handler->prev_pipe_in_fd);
		if (handler->last_cmd_flag != TRUE)
		{
			handler->prev_pipe_in_fd = pipe_fd[IN];
			return (pipe_fd[IN]);
		}
		else
		{
			close(pipe_fd[IN]);
			return (-1);
		}
	}
}

exec_in_dfs(t_exec_handler handler)
{
	if (handler.cur_node->left != NULL)
	{
		handler.cur_node= handler.cur_node->left;
		run_exec_in_dfs(handler);
	}
	if (handler.cur_node->cmd_tokens != NULL)
	{
		set_()
		handler.prev_pipe_in_fd = execute_ret_pipe_out_fd();

	}
	if(handler.cur_node->right != NULL)
	{
		handler.cur_node = handler.cur_node->right;
		run_exec_in_dfs(handler);
	}
}