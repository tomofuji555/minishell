/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_in_child.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:19:18 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/15 21:46:34 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../utils/utils.h"

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

int wait_child(t_manager *manager)
{
	int	wait_status;
	int	exit_status;

	exit_status = 0;
	while(manager->fork_count > 0)
	{
		if (wait(&wait_status) == manager->last_pid)
		{
			if (WIFEXITED(wait_status))
				exit_status = WEXITSTATUS(wait_status);
			else if (WIFSIGNALED(wait_status))
				exit_status = signal_flag;
		}
		manager->fork_count--;
	}
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
	wait_child(manager);
}