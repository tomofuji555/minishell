/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:49 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 21:53:14 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include "../libft/libft.h"
#include "../utils/utils.h"
#include "../expansion/expansion.h"

static void	_handle_sigint_in_heredoc(int num)
{
	g_signal_flag = 128 + num;
	ft_xclose(STDIN_FILENO);
}

void	try_heredoc_helper(t_redir *redir_ptr, t_manager *manager)
{
	while (redir_ptr != NULL && g_signal_flag == 0)
	{
		if (redir_ptr->kind == REDIR_HEREDOC || \
			redir_ptr->kind == REDIR_HEREDOC_NO_EXPAND)
			redir_ptr->val = run_heredoc(redir_ptr, manager);
		redir_ptr = redir_ptr->next;
	}
}

void	try_heredoc(t_tree_node *ptr, t_manager *manager)
{
	signal(SIGINT, _handle_sigint_in_heredoc);
	while (ptr->left != NULL)
		ptr = ptr->left;
	try_heredoc_helper(ptr->adv_data.infile_paths, manager);
	while (ptr != NULL)
	{
		if (ptr->right != NULL)
			try_heredoc_helper(ptr->right->adv_data.infile_paths, manager);
		ptr = ptr->prev;
	}
}
