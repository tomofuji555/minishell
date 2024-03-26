/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:17 by toshi             #+#    #+#             */
/*   Updated: 2024/03/27 05:44:34 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*make_cmd_path(char *cmd_name, t_env *env_list)
{
	char	**path_list;
	char	*cmd_path;
	size_t	i;

	path_list = ft_xsplit(ft_getenv("PATH", env_list), ':');
	i = 0;
	while (path_list[i] != NULL)
	{
		cmd_path = join_and_free_str2(path_list[i], ft_xstrjoin("/", cmd_name));
		if (access(cmd_path, F_OK) == EXIST)
		{
			free_multi_strs(path_list);
			return (cmd_path);
		}
		else
			free(cmd_path);
		i++;
	}
	free_multi_strs(path_list);
	return (NULL);
}

static void	exec_external_cmd(char **cmd_args, t_env *env_list)
{
	char		*cmd_path;

	if (cmd_args == NULL)
		exit (0);
	if (is_cmd_path(cmd_args[0]))
	{
		if (access(cmd_args[0], F_OK) != EXIST)
			perror_arg2_and_exit(cmd_args[0], "No such file or directory", 127);	
		ft_xexecve(cmd_args[0], cmd_args, env_list);
	}
	cmd_path = make_cmd_path(cmd_args[0], env_list);
	if (cmd_path == NULL)
		perror_arg2_and_exit(cmd_args[0], "command not found", 127);
	ft_xexecve(cmd_path, cmd_args, env_list);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */


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
static t_bool	can_change_stream_redirect(t_redir *redir_head, int dest_fd)
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


static void	change_instream(t_redir *redir_head, int prev_outfd)
{
	if (redir_head)
	{
		
		if (!can_change_stream_redirect(redir_head, STDIN_FILENO))
		{
			exit(1);
		}
		if (prev_outfd != STDIN_FILENO)
			ft_xclose(prev_outfd);
	}
	else
	{
		if (prev_outfd != STDIN_FILENO)
		{
			ft_xdup2(prev_outfd, STDIN_FILENO);
			ft_xclose(prev_outfd);
		}
	}
}

static void	change_outstream(t_redir *redir_head, int pipefd_out, t_bool last_cmd_flag)
{
	if (redir_head)
	{
		if (!can_change_stream_redirect(redir_head, STDOUT_FILENO))
			exit(1);
		if (last_cmd_flag != TRUE)
			ft_xclose(pipefd_out);
	}
	else
	{
		if (last_cmd_flag != TRUE)
		{
			ft_xdup2(pipefd_out, STDOUT_FILENO);
			ft_xclose(pipefd_out);
		}
	}
}

static void	update_prev_outfd(t_manager *manager, int pipefd_in, t_bool last_cmd_flag)
{
	//if (!manager->first_cmd_flag)
	if (manager->prev_outfd != STDIN_FILENO)
		ft_xclose(manager->prev_outfd);
	if (last_cmd_flag)
		ft_xclose(pipefd_in);
	else
		manager->prev_outfd = pipefd_in;
}

static pid_t fork_and_exec_cmd(t_refine_data data, t_manager *manager, t_bool last_cmd_flag)
{
	int		pipefd[2];
	pid_t	pid;

	ft_xpipe(pipefd);
	pid = ft_xfork();
	if (pid == CHILD)
	{
		ft_xclose(pipefd[R]);
		change_instream(data.infile_paths, manager->prev_outfd);
		change_outstream(data.outfile_paths, pipefd[W], last_cmd_flag);
		//if (!try_do_builtin_and_eixt(data.cmd_args, manager))
		exec_external_cmd(data.cmd_args, manager->env_list);
	}
	ft_xclose(pipefd[W]);
	update_prev_outfd(manager, pipefd[R], last_cmd_flag);
	return (pid);
}

void	exec_cmd_in_child(t_tree_node *ptr, t_manager *manager)
{
	while(ptr != NULL)
	{
		if (is_cmd_node(ptr))
		{
			manager->last_pid = fork_and_exec_cmd(ptr->refine_data, manager, is_last_cmd(ptr));
			manager->fork_count++;
		}
		ptr = ptr->right;
	}
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

int	do_builtin(char **cmd_args, t_manager *manager)
{
	if (is_equal_str(*cmd_args, "cd"))
		return (do_cd(cmd_args, manager));
	//if (!cmd_args)
	//	return (-1);
	//if (is_equal_str(*cmd_args, "echo"))
	//	return (ms_echo(cmd_args));
	//else if (is_equal_str(*cmd_args, "cd"))
	//	rerurn (ms_cd(cmd_args, envp));
	//else if (is_equal_str(*cmd_args, "pwd"))
	//	return (ms_pwd(envp));
	//else if (is_equal_str(*cmd_args, "export"))
	//	return (ms_export(cmd_args, envp));
	//else if (is_equal_str(*cmd_args, "unset"))
	//	return (ms_unset(cmd_args, envp));
	//else if (is_equal_str(*cmd_args, "env"))
	//	return (ms_env(envp));
	//else if (is_equal_str(*cmd_args, "exit"))
	//	return (ms_exit(cmd_args, envp));
	else
		return (-1);
}

t_bool	can_change_iostream_redirect(t_refine_data data)
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

void do_single_builtin(t_tree_node *root, t_manager *manager)
{
	int tmpfd_in;
	int tmpfd_out;

	tmpfd_in = STDIN_FILENO;
	tmpfd_out = STDOUT_FILENO;
	if (can_change_iostream_redirect(root->refine_data))
		manager->exit_status = do_builtin(root->refine_data.cmd_args, manager);
	else
		manager->exit_status = 1;
	ft_xdup2(tmpfd_in, STDIN_FILENO);
	ft_xdup2(tmpfd_out, STDOUT_FILENO);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

static void wait_child(t_manager *manager)
{
	int	status;

	//system("ps");
	while(manager->fork_count > 0)
	{
		if (wait(&status) == manager->last_pid)
			manager->exit_status = WEXITSTATUS(status);
		manager->fork_count--;
	}
	//system("ps");
}

void	execute(t_tree_node *root, t_manager *manager)
{
	int tmpfd_in;
	
	tmpfd_in = STDIN_FILENO;
	if (is_single_builtin(root))
		do_single_builtin(root, manager);
	else
		exec_cmd_in_child(root, manager);
	wait_child(manager);
	manager->prev_outfd = tmpfd_in;
	manager->last_cmd_flag = FALSE;
	manager->fork_count = 0;
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */