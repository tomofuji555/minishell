/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:49 by toshi             #+#    #+#             */
/*   Updated: 2024/04/18 20:44:19 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../utils/utils.h"
#include "../expansion/expansion.h"



static void _handle_sigint_in_heredoc(int num)
{
	signal_flag = 128 + num;
	ft_xclose(STDIN_FILENO);
}

void	try_heredoc(t_tree_node *tnode_head, t_manager *manager)
{
	t_tree_node *ptr;
	t_redir	*redir_ptr;

	signal(SIGINT, _handle_sigint_in_heredoc);
	ptr = tnode_head;
	while (ptr != NULL && signal_flag == 0)
	{
		redir_ptr = ptr->adv_data.infile_paths;
		while (redir_ptr != NULL && signal_flag == 0)
		{
			if (redir_ptr->kind == REDIR_HEREDOC || \
				redir_ptr->kind == REDIR_HEREDOC_NO_EXPAND)
				redir_ptr->val = run_heredoc(redir_ptr, manager);
			redir_ptr = redir_ptr->next;
		}
		ptr = ptr->right;
	}
}
