/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:11:27 by toshi             #+#    #+#             */
/*   Updated: 2024/04/27 17:08:42 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include "../utils/utils.h"

static void	_change_instream(t_redir *redir_list, int prevfd_in)
{
	if (redir_list)
	{
		if (!try_change_stream_redirect(redir_list, STDIN_FILENO))
			exit(1);
		if (prevfd_in != STDIN_FILENO)
			ft_xclose(prevfd_in);
	}
	else
	{
		if (prevfd_in != STDIN_FILENO)
		{
			ft_xdup2(prevfd_in, STDIN_FILENO);
			ft_xclose(prevfd_in);
		}
	}
}

static void	_change_outstream(t_redir *redir_list, int pipefd_out, \
			t_bool last_cmd_flag)
{
	if (redir_list)
	{
		if (!try_change_stream_redirect(redir_list, STDOUT_FILENO))
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

static t_bool	_try_exec_builtin(char **cmd_args, t_manager *manager)
{
	int	exit_status;

	exit_status = do_builtin(cmd_args, manager);
	if (exit_status == -1)
		return (FALSE);
	exit(exit_status);
}

pid_t	fork_and_exec_cmd(t_adv_data adv, t_manager *manager, t_exec_data *exec)
{
	int		pipefd[2];
	pid_t	pid;

	ft_xpipe(pipefd);
	pid = ft_xfork();
	if (pid == CHILD)
	{
		ft_xclose(pipefd[R]);
		_change_outstream(adv.outfile_paths, pipefd[W], exec->last_cmd_flag);
		_change_instream(adv.infile_paths, exec->prevfd_in);
		if (adv.cmd_args != NULL && !_try_exec_builtin(adv.cmd_args, manager))
			exec_external_cmd(adv.cmd_args, manager);
		exit(0);
	}
	ft_xclose(pipefd[W]);
	if (exec->prevfd_in != STDIN_FILENO)
		ft_xclose(exec->prevfd_in);
	if (exec->last_cmd_flag)
		ft_xclose(pipefd[R]);
	else
		exec->prevfd_in = pipefd[R];
	return (pid);
}

void	wait_child(t_manager *manager, t_exec_data exec)
{
	int	wait_status;

	while (exec.fork_count > 0)
	{
		if (wait(&wait_status) == exec.last_pid)
		{
			if (WIFEXITED(wait_status))
				update_exit_status(manager, WEXITSTATUS(wait_status));
			else if (WIFSIGNALED(wait_status))
				update_exit_status(manager, g_signal_flag);
		}
		exec.fork_count--;
	}
}
