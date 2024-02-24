/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:17 by toshi             #+#    #+#             */
/*   Updated: 2024/02/24 18:52:32 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*search_and_make_path(char *cmd_name, char **envp)
{
	char	**path_lst;
	char	*cmd_path;
	size_t	i;

	path_lst = ft_xsplit(ft_getenv("PATH"), ':');
	i = 0;
	while (path_lst[i] != NULL)
	{
		cmd_path = ft_xstrjoin(path_lst[i], ft_xstrjoin("/", cmd_name));  //リークの関係上、作り直す必要あり
		if (access(cmd_path, F_OK) == EXIST)
		{
			free_multi_strs(path_lst);
			return (cmd_path);
		}
		else
			free(cmd_path);
		i++;
	}
	free_multi_strs(path_lst);
	return (NULL);
}

//cmd_argsがNULL出ない前提で作成
void	exec_cmd(char **cmd_args, char **envp)
{
	char		*cmd_path;

	if (is_absolute_path_cmd(cmd_args[0]))
	{
		if (access(cmd_args[0], F_OK) != EXIST)
			ft_perror_and_exit(cmd_args[0], "No such file or directory", 127);	
		ft_xexecve(cmd_args[0], cmd_args, envp);
		return ;
	}
	cmd_path = search_and_make_path(cmd_args[0], envp);
	if (cmd_path == NULL)
		ft_perror_and_exit(cmd_args[0], "command not found", 127);
	ft_xexecve(cmd_path, cmd_args, envp);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

static int open_redir_path(t_redir *node)
{
	int fd;

	if(ft_strchr(node->val, ' '))
	{
		ft_perror_and_exit(node->val, "ambiguous redirect", 1);
		return (SYS_FAILURE);
	}
	if (node->kind == REDIR_OUT_FILE)
		fd = open(node->val, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	else if (node->kind == REDIR_APPEND_FILE)
		fd = open(node->val, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	else
		fd = open(node->val, O_RDONLY);
	if (fd == SYS_FAILURE)
		perror(node->val); //No such file or directory / Permission denied を勝手に吐いてくれる
	return (fd);
}

static int fd_find_last(t_redir *redir_ptr)
{
	int fd;

	fd = DEFAULT;
	while(redir_ptr != NULL)
	{
		if (fd != DEFAULT)
			ft_xclose(fd);
		fd = open_redir_path(redir_ptr);
		if (fd == SYS_FAILURE)
			return (fd);
		redir_ptr = redir_ptr->next;
	}
	return (fd);
}

//redir_headがNULLじゃない前提で実装
t_bool	can_change_stream_to_redir(t_redir *redir_head, int dest_fd)
{
	int redir_fd;

	redir_fd = fd_find_last(redir_head);
	if (redir_fd == SYS_FAILURE)
		return (FALSE);
	ft_xdup2 (redir_fd, dest_fd);
	ft_xclose(redir_fd);
	return (TRUE);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

t_bool change_instream(t_redir *redir_head, int prev_output_fd)
{
	if (redir_head)
	{
		if (can_change_stream_to_redir(redir_head, STDIN_FILENO) == FALSE)
			return (FALSE);
		if (prev_output_fd != STDIN_FILENO)
			ft_xclose(prev_output_fd);
	}
	else
	{
		if (prev_output_fd != STDIN_FILENO)
		{
			ft_xdup2(prev_output_fd, STDIN_FILENO);
			ft_xclose(prev_output_fd);
		}
	}
	return (TRUE);
}

t_bool change_outstream(t_redir *redir_head, int pipe_out_fd, t_bool last_cmd_flag)
{
	if (redir_head)
	{
		if (can_change_stream_to_redir(redir_head, STDOUT_FILENO) == FALSE)
			return (FALSE);
		if (last_cmd_flag != TRUE)
			ft_xclose(pipe_out_fd);
	}
	else
	{
		if (last_cmd_flag != TRUE)
		{
			ft_xdup2(pipe_out_fd, STDOUT_FILENO);
			ft_xclose(pipe_out_fd);
		}
	}
	return (TRUE);
}

void update_prev_fd(t_manager *manager, int *pipefd, t_bool last_cmd_flag)
{
	ft_xclose(pipefd[W]);
	//if (!manager->first_cmd_flag)
	if (manager->prev_output_fd != STDIN_FILENO)
		ft_xclose(manager->prev_output_fd);
	if (last_cmd_flag)
		ft_xclose(pipefd[R]);
	else
		manager->prev_output_fd = pipefd[R];
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

pid_t exec_external_cmd(t_exec_data data, t_manager *manager, t_bool last_cmd_flag)
{
	int		pipe_fd[2];
	pid_t	pid;
	extern	char **environ;

	ft_xpipe(pipe_fd);
	pid = ft_xfork();
	if (pid == CHILD)
	{
		ft_xclose(pipe_fd[R]);
		if (change_instream(data.infile_paths, manager->prev_output_fd) == TRUE
			&& change_outstream(data.outfile_paths, pipe_fd[W], last_cmd_flag) == TRUE)
			exec_cmd(data.cmd_args, environ);
		exit(1);
	}
	update_prev_fd(manager, pipe_fd, last_cmd_flag);
	return (pid);
}

void	_exec(t_tree_node *ptr, t_manager *manager)
{
	pid_t	last_pid;
	size_t	fork_count;
	int		status;

	fork_count = 0;
	while(ptr != NULL)
	{
		if (is_cmd_node(ptr))
		{
			//ビルトインかつ、１つだけのコマンドなら親プロセスで実行
				//exec_single_builtin_cmd();
			//ビルトインかつ複数あるコマンドなら子プロセスで実行
				//exec_builtin_cmd();
			last_pid = exec_external_cmd(ptr->exec_data, manager, is_last_cmd(ptr));
			fork_count++;
		}
		ptr = ptr->right;
	}
	while(fork_count > 0)
	{
		if (wait(&status) == last_pid)
			manager->exit_status = WEXITSTATUS(status);
		fork_count--;
	}
}



//exec_in_while(t_tree_node *root_node)
//{
//	t_tree_node *cur_node;

//	cur_node = root_node;
//	while (cur_node->left != NULL)
//		cur_node = cur_node->left;
//	do_exec(cur_node); //forkし、ストリームを変え、実行、prev_fd＆last_pidを更新
//	while (cur_node != NULL)
//	{
//		if (cur_node->right != NULL)
//			de_exec(cur_node->right->exec_arg_data); //forkし、ストリームを変え、実行、prev_fd＆last_pidを更新
//		cur_node = cur_node->prev;
//	}
//	while(0) //forkしたカウント
//	{
//		if (pid == wait(&status)) //last_pidとwaitの返り値が同じなら
//			printf("最終終了ステータス%d\n", WEXITSTATUS(status));
//	}
//}