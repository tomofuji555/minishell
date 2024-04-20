/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:01:49 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 18:44:37 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include "../utils/utils.h"

static t_bool	_is_builtin(char *cmd)
{
	return (is_equal_str(cmd, "cd") \
	|| is_equal_str(cmd, "echo") \
	|| is_equal_str(cmd, "env") \
	|| is_equal_str(cmd, "exit") \
	|| is_equal_str(cmd, "export") \
	|| is_equal_str(cmd, "pwd") \
	|| is_equal_str(cmd, "unset"));
}

t_bool	is_single_builtin(t_tree_node *tnode_head)
{
	return (tnode_head->left == NULL \
	&& tnode_head->right == NULL \
	&& tnode_head->prev == NULL \
	&& _is_builtin(tnode_head->adv_data.cmd_args[0]));
}
