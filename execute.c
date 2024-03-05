/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:17 by toshi             #+#    #+#             */
/*   Updated: 2024/03/05 08:30:49 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	change_instream(t_redir *redir_head, int prev_output_fd)
{
	if (redir_head)
	{
		if (!can_change_stream_redirect(redir_head, STDIN_FILENO))
			exit(1);
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
}

void	change_outstream(t_redir *redir_head, int pipe_out_fd, t_bool last_cmd_flag)
{
	if (redir_head)
	{
		if (!can_change_stream_redirect(redir_head, STDOUT_FILENO))
			exit(1);
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
}

void	update_prev_outfd(t_manager *manager, int pipefd_in, t_bool last_cmd_flag)
{
	//if (!manager->first_cmd_flag)
	if (manager->prev_output_fd != STDIN_FILENO)
		ft_xclose(manager->prev_output_fd);
	if (last_cmd_flag)
		ft_xclose(pipefd_in);
	else
		manager->prev_output_fd = pipefd_in;
}

pid_t exec_cmd_in_child(t_exec_data data, t_manager *manager, t_bool last_cmd_flag)
{
	int		pipefd[2];
	pid_t	pid;
	extern	char **environ;

	ft_xpipe(pipefd);
	pid = ft_xfork();
	if (pid == CHILD)
	{
		ft_xclose(pipefd[R]);
		change_instream(data.infile_paths, manager->prev_output_fd);
		change_outstream(data.outfile_paths, pipefd[W], last_cmd_flag);
		if (!try_do_builtin_and_eixt())
			exec_external_cmd(data.cmd_args, environ);
	}
	ft_xclose(pipefd[W]);
	update_prev_outfd(manager, pipefd[R], last_cmd_flag);
	return (pid);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

