#include "execute.h"

int change_input_fd(t_exec_handler *handler)
{
	if (handler->infile_paths)
		change_input_infile(handler->infile_paths);
		// if (infile) //ファイルからread
		// in_fd = open(infile)
		// dup2(in_fd, stdIN)
		// close(in_fd)
		// close(prev_pipe_in)
	else
	{
		if (handler->prev_pipe_in_fd != STDIN_FILENO)
			dup2(handler->prev_pipe_in_fd, STDIN_FILENO);
		close(handler->prev_pipe_in_fd);
	}
}


int change_output_fd(t_exec_handler *handler, int pipe_out_fd)
{
	if (handler->outfile_paths)
		change_output_infile(handler->outfile_paths, pipe_out_fd);
		// if (outfile) //ファイルへwrite
		// out_fd = open(outfile)
		// dup2(out_fd, stdOUT)
		// close(out_fd)
		// close(pipe_out)
	else
	{
		if (handler->last_cmd_flag != TRUE)
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
			// handler->prev_pipe_in_fd = pipe_fd[IN];
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