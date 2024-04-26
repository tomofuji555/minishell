/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:19:18 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/26 19:08:50 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../utils/utils.h"

static t_exec_data	init_exec_data(void)
{
	t_exec_data	exec;

	exec.prevfd_in = STDIN_FILENO;
	exec.fork_count = 0;
	exec.last_cmd_flag = FALSE;
	return (exec);
}

static t_bool	is_last_cmd(t_tree_node *ptr)
{
	return (ptr->prev == NULL \
	|| (ptr->prev->right == ptr && ptr->prev->prev == NULL));
}

static void	exec_cmd_helper(t_tree_node *ptr, t_manager *manager, \
	t_exec_data *exec)
{
	exec->last_cmd_flag = is_last_cmd(ptr);
	exec->last_pid = fork_and_exec_cmd(ptr->adv_data, manager, exec);
	exec->fork_count++;
}

void	exec_cmds(t_tree_node *ptr, t_manager *manager)
{
	t_exec_data	exec;

	exec = init_exec_data();
	while (ptr->left != NULL)
		ptr = ptr->left;
	exec_cmd_helper(ptr, manager, &exec);
	while (ptr != NULL)
	{
		if (ptr->right != NULL)
			exec_cmd_helper(ptr->right, manager, &exec);
		ptr = ptr->prev;
	}
	wait_child(manager, exec);
}
