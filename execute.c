/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:17 by toshi             #+#    #+#             */
/*   Updated: 2024/02/08 07:39:11 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int open_redir_path(t_redir *node)
{
	int fd;
	
	if (node->kind == REDIR_OUT_FILE)
		fd = open(node->val, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	else if (node->kind == REDIR_APPEND_FILE)
		fd = open(node->val, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	else
		fd = open(node->val, O_RDONLY);
	return (fd);
}

static int fd_find_last(t_redir *redir_ptr)
{
	int fd;

	fd = -1;
	while(redir_ptr->next != NULL)
	{
		if (fd > -1)
			close(fd);
		fd = _open_redir_path(redir_ptr);
		if (fd == SYS_FAILURE)
			return (fd);//error文吐く、exitするのは外
		redir_ptr = redir_ptr->next;
	}
	return (fd);
}

//redir_headがNULLじゃない前提で実装
void	change_stream_to_redir(t_redir *redir_head, int dest_fd)
{
	int redir_fd;

	redir_fd = _fd_find_last(redir_head);
	if (redir_fd == SYS_FAILURE)
		;//FALSEを返す
	ft_xdup2 (redir_fd, dest_fd);
	ft_xclose(redir_fd);
}

static char	*search_and_make_path(char *cmd_name, char **envp)
{
	char	**path_lst;
	char	*cmd_path;
	size_t	i;

	path_lst = ft_xsplit(ft_getenv("PATH"), ':'); //xsplitに
	i = 0;
	while (path_lst[i] != NULL)
	{
		cmd_path = ft_xstrjoin(path_lst[i], ft_xstrjoin("/", cmd_name));
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

	if (ft_strchr(cmd_args[0], '/') != NULL || access(cmd_args[0], F_OK) == EXIST)
	{
		if (access(cmd_args[0], X_OK) == -1)
			perror_and_exit(NULL, 1);	
		ft_xececve(cmd_args[0], cmd_args, envp);
		return ;
	}
	cmd_path = search_and_make_path(cmd_args[0], envp);
	if (cmd_path == NULL)
	{
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return ;
	}
	if (access(cmd_path, X_OK) == -1)
		perror_and_exit(NULL, 1);
	ft_xexecve(cmd_path, cmd_args, envp);
}

void change_instream(t_redir *redir_head, int prev_output_fd)
{
	//if (redir_head)
	//	change_stream_to_redir(redir_head, STDIN_FILENO);
	//else
	//{
		if (prev_output_fd != STDIN_FILENO)
			ft_xdup2(prev_output_fd, STDIN_FILENO);
	//}
	ft_xclose(prev_output_fd);
}

void change_outstream(t_redir *redir_head, int pipe_out_fd, t_bool last_cmd_flag)
{
	//if (redir_head)
	//	change_stream_to_redir(redir_head, STDOUT_FILENO);
	//else
	//{
		if (last_cmd_flag == TRUE)
			ft_xdup2(pipe_out_fd, STDOUT_FILENO);
	//}
	ft_xclose(pipe_out_fd);
}

void update_prev_fd(t_manager *manager, int *pipefd, t_bool last_cmd_flag)
{
	ft_xclose(pipefd[W]);
	if (last_cmd_flag)
	{
		if (!manager->first_cmd_flag)
			ft_xclose(manager->prev_output_fd);
		ft_xclose(pipefd[R]);
		return ;
	}
	if (!manager->first_cmd_flag)
		ft_xclose(manager->prev_output_fd);
	manager->prev_output_fd = pipefd[W];
}


int exec_external_cmd(t_exec_data data, t_manager manager, t_bool last_cmd_flag)
{
	int		pipe_fd[2];
	pid_t	pid;

	ft_xpipe(pipe_fd);
	pid = ft_xfork();
	if (pid == CHILD)
	{
		change_instream(data.infile_paths, manager.prev_output_fd);
		change_outstream(data.outfile_paths, pipe_fd[W], last_cmd_flag);
		exec_cmd(data.cmd_args, manager.envp);
	}
	else
		update_prev_fd(&manager, pipe_fd, last_cmd_flag);
}

void	do_exec(t_exec_data data, t_manager manager)
{
	//if (is_builtin(ptr->exec_data.cmd_args[0]))
	//	exec_builtin_cmd(ptr, manager);
	//else
		exec_external_cmd(data, manager);
}

void	exec_tmp(t_tree_node *ptr, t_manager manager)
{
	while (ptr != NULL)
	{
		do_exec(ptr->exec_data, manager);
		ptr = ptr->right;
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