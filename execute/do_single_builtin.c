/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_single_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:59:20 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/20 17:27:55 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include "../builtin/builtin.h"
#include "../utils/utils.h"

int	do_builtin(char **cmd_args, t_manager *manager)
{
	if (is_equal_str(*cmd_args, "cd"))
		return (do_cd(cmd_args, manager));
	else if (is_equal_str(*cmd_args, "echo"))
		return (do_echo(cmd_args));
	else if (is_equal_str(*cmd_args, "env"))
		return (do_env(cmd_args, manager));
	else if (is_equal_str(*cmd_args, "exit"))
		return (do_exit(cmd_args, manager));
	else if (is_equal_str(*cmd_args, "export"))
		return (do_export(cmd_args, manager));
	else if (is_equal_str(*cmd_args, "unset"))
		return (do_unset(cmd_args, manager));
	else if (is_equal_str(*cmd_args, "pwd"))
		return (do_pwd(manager));
	else if (is_equal_str(*cmd_args, "unset"))
		return (do_unset(cmd_args, manager));
	else
		return (-1);
}

static t_bool	_try_change_iostream_redirect(t_adv_data data)
{
	if (data.infile_paths)
	{
		if (!try_change_stream_redirect(data.infile_paths, STDIN_FILENO))
			return (FALSE);
	}
	if (data.outfile_paths)
	{
		if (!try_change_stream_redirect(data.outfile_paths, STDOUT_FILENO))
			return (FALSE);
	}
	return (TRUE);
}

void	do_single_builtin(t_tree_node *root, t_manager *manager)
{
	int	tmpfd_in;
	int	tmpfd_out;
	int	status;

	tmpfd_in = ft_xdup(STDIN_FILENO);
	tmpfd_out = ft_xdup(STDOUT_FILENO);
	status = 1;
	if (_try_change_iostream_redirect(root->adv_data))
		status = do_builtin(root->adv_data.cmd_args, manager);
	update_exit_status(manager, status);
	ft_xdup2(tmpfd_in, STDIN_FILENO);
	ft_xdup2(tmpfd_out, STDOUT_FILENO);
}
