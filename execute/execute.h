/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/04/15 20:01:42 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "../minishell.h"

enum	e_pipefd_direct
{
	R	= 0,
	W	= 1
};

//~~~~execute start~~~~
void	exec_cmd_in_child(t_tree_node *ptr, t_manager *manager);
void	execute(t_tree_node *root, t_manager *manager);

void do_single_builtin(t_tree_node *root, t_manager *manager);
//~~~~~~~~

//~~~~heredoc start~~~~
void	rm_heredoc_tmp(t_tree_node *tnode_head);
void	try_heredoc(t_tree_node *tnode_head, t_manager *manager);
//~~~~~~~~



#endif 