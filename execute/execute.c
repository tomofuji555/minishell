/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:17 by toshi             #+#    #+#             */
/*   Updated: 2024/04/19 21:06:05 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

void _handle_sigint_in_exec(int num)
{
	signal_flag = 128 + num;
	ft_putchar_fd('\n', STDERR_FILENO);
}

//cat | cat と cat | ls で出力が違う 
void _handle_sigquit_in_exec(int num)
{
	signal_flag = 128 + num;
	ft_putendl_fd("Quit: 3", STDERR_FILENO);
}

void	execute(t_tree_node *root, t_manager *manager)
{
	try_heredoc(root, manager);
	if (signal_flag == 0)
	{
		signal(SIGINT, _handle_sigint_in_exec);
		signal(SIGQUIT, _handle_sigquit_in_exec);
		if (is_single_builtin(root))
			do_single_builtin(root, manager);
		else
			exec_cmds(root, manager);
	}
	else
		update_exit_status(manager, signal_flag);
	remove_heredoc_tmpfile(root);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */