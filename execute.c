/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:17 by toshi             #+#    #+#             */
/*   Updated: 2024/04/10 21:26:45 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*make_cmd_path(char *cmd_name, t_manager *manager)
{
	char	**path_list;
	char	*cmd_path;
	size_t	i;

	path_list = ft_xsplit(ft_getenv("PATH", manager) , ':');
	if (path_list != NULL)
	{
		i = 0;
		while (path_list[i] != NULL)
		{
			cmd_path = join_and_free_str2(path_list[i], ft_xstrjoin("/", cmd_name));
			if (access(cmd_path, F_OK) == EXIST && !opendir(cmd_path))
			{
				free_multi_strs(path_list);
				return (cmd_path);
			}
			else
				free(cmd_path);
			i++;
		}
		free_multi_strs(path_list);
	}
	if (access(cmd_name, F_OK) == EXIST && !opendir(cmd_name))
		return (cmd_name);
	return (NULL);
}

static void	exec_external_cmd(char **cmd_args, t_manager *manager)
{
	char		*cmd_path;

	if (cmd_args == NULL)
		exit (0);
	if (is_cmd_path(cmd_args[0]))
	{
		if (opendir(cmd_args[0]))
			perror_arg2_and_exit(cmd_args[0], "Is a directory", 126);
		if (access(cmd_args[0], F_OK) != EXIST)
			perror_arg2_and_exit(cmd_args[0], "No such file or directory", 127);
		ft_xexecve(cmd_args[0], cmd_args, manager->env_list);
	}
	cmd_path = make_cmd_path(cmd_args[0], manager);
	if (cmd_path == NULL)
		perror_arg2_and_exit(cmd_args[0], "command not found", 127);
	ft_xexecve(cmd_path, cmd_args, manager->env_list);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */


static int open_redir_path(t_redir *node)
{
	int fd;

	if (node->kind == REDIR_OUT_FILE)
		fd = open(node->val, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (node->kind == REDIR_APPEND_FILE)
		fd = open(node->val, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(node->val, O_RDONLY);
	if (fd == SYS_FAILURE)
		perror(node->val); //No such file or directory / Permission denied を勝手に吐いてくれる
	return (fd);
}
	// if (node->kind == AMBIGUOUS_REDIR)
	// {
	// 	perror_arg2(node->val, "ambiguous redirect");
	// 	return (SYS_FAILURE);
	// }
	//if(is_equal_str(node->val, "") || ft_strchr(node->val, ' '))
	//{
	//	perror_arg2(node->val, "ambiguous redirect");
	//	return (SYS_FAILURE);
	//}

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
			exit(1);
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

static pid_t fork_and_exec_cmd(t_adv_data data, t_manager *manager, t_bool last_cmd_flag)
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
		// if (!try_do_builtin_and_eixt(data.cmd_args, manager))
		exec_external_cmd(data.cmd_args, manager);
		exit(0);
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
			manager->last_pid = fork_and_exec_cmd(ptr->adv_data, manager, is_last_cmd(ptr));
			
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
	else if (is_equal_str(*cmd_args, "exit"))
		return (do_exit(cmd_args, manager));
	else if (is_equal_str(*cmd_args, "export"))
		return (do_export(cmd_args, manager));
	else if (is_equal_str(*cmd_args, "env"))
		return (do_env(cmd_args, manager));
	else if (is_equal_str(*cmd_args, "unset"))
		return (do_unset(cmd_args, manager));
	// //if (!cmd_args)
	// //	return (-1);
	// //if (is_equal_str(*cmd_args, "echo"))
	// //	return (ms_echo(cmd_args));
	// //else if (is_equal_str(*cmd_args, "cd"))
	// //	rerurn (ms_cd(cmd_args, envp));
	// //else if (is_equal_str(*cmd_args, "pwd"))
	// //	return (ms_pwd(envp));
	// else
		return (-1);
}

t_bool	can_change_iostream_redirect(t_adv_data data)
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
	if (can_change_iostream_redirect(root->adv_data))
		update_exit_status(manager, do_builtin(root->adv_data.cmd_args, manager));
	else
		update_exit_status(manager, 1);
	ft_xdup2(tmpfd_in, STDIN_FILENO);
	ft_xdup2(tmpfd_out, STDOUT_FILENO);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

static void wait_child(t_manager *manager)
{
	int	status;

	while(manager->fork_count > 0)
	{
		if (wait(&status) == manager->last_pid)
		{
			if (WIFEXITED(status))
				update_exit_status(manager, WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				update_exit_status(manager, signal_flag);
		}
		manager->fork_count--;
	}
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

void handle_sigint_in_exec(int num)
{
	signal_flag = 128 + num;
	ft_putchar_fd('\n', STDERR_FILENO);
}

//cat | cat と cat | ls で出力が違う 
void handle_sigquit_in_exec(int num)
{
	signal_flag = 128 + num;
	ft_putendl_fd("Quit: 3", STDERR_FILENO);
}

void	execute(t_tree_node *root, t_manager *manager)
{
	int tmpfd_in;
	
	signal(SIGINT, handle_sigint_in_exec);
	signal(SIGQUIT, handle_sigquit_in_exec);
	// tmpfd_in = STDIN_FILENO;
	if (is_single_builtin(root))
		do_single_builtin(root, manager);
	else
	{
		exec_cmd_in_child(root, manager);
		wait_child(manager);
	}
	// manager->prev_outfd = STDIN_FILENO;
	// manager->last_cmd_flag = FALSE;
	// manager->fork_count = 0;
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */