/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:17 by toshi             #+#    #+#             */
/*   Updated: 2024/04/15 21:46:35 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../utils/utils.h"


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