/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:06:56 by tozeki            #+#    #+#             */
/*   Updated: 2024/03/05 17:42:41 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int open_redir_path(t_redir *node)
{
	int fd;

	//if(is_equal_str(node->val, "") || ft_strchr(node->val, ' '))
	//{
	//	perror_arg2(node->val, "ambiguous redirect");
	//	return (SYS_FAILURE);
	//}
	if (node->kind == AMBIGUOUS_REDIR)
	{
		perror_arg2(node->val, "ambiguous redirect");
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

static int find_last_fd(t_redir *redir_ptr)
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
t_bool	can_change_stream_redirect(t_redir *redir_head, int dest_fd)
{
	int redir_fd;

	redir_fd = find_last_fd(redir_head);
	if (redir_fd == SYS_FAILURE)
		return (FALSE);
	ft_xdup2 (redir_fd, dest_fd);
	ft_xclose(redir_fd);
	return (TRUE);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

static char	*make_cmd_path(char *cmd_name, char **envp)
{
	char	**path_lst;
	char	*cmd_path;
	size_t	i;

	path_lst = ft_xsplit(ft_getenv("PATH"), ':');
	i = 0;
	while (path_lst[i] != NULL)
	{
		cmd_path = join_and_free_str2(path_lst[i], ft_xstrjoin("/", cmd_name));
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

void	exec_external_cmd(char **cmd_args, char **envp)
{
	char		*cmd_path;

	if (cmd_args == NULL)
		exit (0);
	if (is_cmd_path(cmd_args[0]))
	{
		if (access(cmd_args[0], F_OK) != EXIST)
			perror_arg2_and_exit(cmd_args[0], "No such file or directory", 127);	
		ft_xexecve(cmd_args[0], cmd_args, envp);
	}
	cmd_path = make_cmd_path(cmd_args[0], envp);
	if (cmd_path == NULL)
		perror_arg2_and_exit(cmd_args[0], "command not found", 127);
	ft_xexecve(cmd_path, cmd_args, envp);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

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
			last_pid = exec_cmd_in_child(ptr->exec_data, manager, is_last_cmd(ptr));
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
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */


int	do_builtin(char **cmd_args, char **envp)
{
	if (!cmd_args)
		return (-1);
	if (is_equal_str(*cmd_args, "echo"))
		return (ms_echo(cmd_args));
	else if (is_equal_str(*cmd_args, "cd"))
		rerurn (ms_cd(cmd_args, envp));
	else if (is_equal_str(*cmd_args, "pwd"))
		return (ms_pwd(envp));
	else if (is_equal_str(*cmd_args, "export"))
		return (ms_export(cmd_args, envp));
	else if (is_equal_str(*cmd_args, "unset"))
		return (ms_unset(cmd_args, envp));
	else if (is_equal_str(*cmd_args, "env"))
		return (ms_env(envp));
	else if (is_equal_str(*cmd_args, "exit"))
		return (ms_exit(cmd_args, envp));
	else
		return (-1);
}

t_bool	can_change_iostream_redirect(t_exec_data data)
{
	if (data.infile_paths)
	{
		if (!can_change_stream_redirect(data.infile_paths, STDIN_FILENO))
			return (FALSE);
	}
	if (data.outfile_paths)
	{
		if (!can_change_stream_redirect(data.outfile_paths, STDOUT_FILENO))
			return (FALSE);
	}
	return (TRUE);
}

void do_single_builtin(t_exec_data data, t_manager *manager)
{
	int tmpfd_in;
	int tmpfd_out;

	tmpfd_in = STDIN_FILENO;
	tmpfd_out = STDOUT_FILENO;
	if (can_change_iostream_redirect(data))
		manager->exit_status = do_builtin(data.cmd_args, manager->envp);
	else
		manager->exit_status = 1;
	ft_xdup2(tmpfd_in, STDIN_FILENO);
	ft_xdup2(tmpfd_out, STDOUT_FILENO);
}

t_bool	try_do_builtin_and_eixt()
{
	int status;

	status = do_builtin();
	if (status == -1)
		return (FALSE);
	exit(status);
	return (TRUE);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

void	execute(t_tree_node *root, t_manager *manager)
{
	//if (root->left == NULL && root->right == NULL)
	if (root->right == NULL)
		do_single_builtin();
	else
		_exec();
}

//exec_in_while(t_tree_node *root)
//{
//	t_tree_node *ptr;

//	ptr = root;
//	while (ptr->left != NULL)
//		ptr = ptr->left;
//	do_exec(ptr); //forkし、ストリームを変え、実行、prev_fd＆last_pidを更新
//	while (ptr != NULL)
//	{
//		if (is_cmd_node())
//			de_exec(ptr->right->exec_arg_data); //forkし、ストリームを変え、実行、prev_fd＆last_pidを更新
//		ptr = ptr->prev;
//	}
//}
