/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:19:18 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/19 21:00:35 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../utils/utils.h"

t_exec_data _init_exec_data()
{
	t_exec_data exec;

	exec.prev_outfd = STDIN_FILENO;
	exec.fork_count = 0;
	exec.last_cmd_flag = FALSE;
	return (exec);
}

static t_bool _is_last_cmd(t_tree_node *ptr)
{
	return (ptr->right == NULL);
	//return (ptr->prev == NULL || ptr->prev->prev == NULL);
}

void	exec_cmds(t_tree_node *ptr, t_manager *manager)
{
	t_exec_data exec;

	exec = _init_exec_data();
	while(ptr != NULL)
	{
		if (is_cmd_node(ptr))
		{
			exec.last_cmd_flag = _is_last_cmd(ptr);
			exec.last_pid = fork_and_exec_cmd(ptr->adv_data, manager, &exec);
			exec.fork_count++;
		}
		ptr = ptr->right;
	}
	wait_child(manager, exec);
}