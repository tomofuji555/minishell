/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:01:49 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 18:58:01 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include "../utils/utils.h"

static t_bool	is_builtin(char *cmd)
{
	return (is_equal_str(cmd, "cd") \
	|| is_equal_str(cmd, "echo") \
	|| is_equal_str(cmd, "env") \
	|| is_equal_str(cmd, "exit") \
	|| is_equal_str(cmd, "export") \
	|| is_equal_str(cmd, "pwd") \
	|| is_equal_str(cmd, "unset"));
}

t_bool	is_single_builtin(t_tree_node *root)
{
	return (root->left == NULL \
	&& root->prev == NULL \
	&& root->adv_data.cmd_args != NULL \
	&& is_builtin(root->adv_data.cmd_args[0]));
}
