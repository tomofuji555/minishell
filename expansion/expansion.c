/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:19:04 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 21:11:47 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../utils/utils.h"
#include "../token/tokenize.h"

//引数を**型にしないと反映されない
//syntaxは保証されている前提で実装
static void	expansion_token_list(t_token **head, t_manager *manager)
{
	t_token	*ptr;

	ptr = *head;
	while (ptr != NULL)
	{
		if (ptr->kind == TKN_HEREDOC)
			ptr = find_last_valuable_token(ptr->next)->next;
		else if (ptr->kind == TKN_ENV)
			ptr = expand_env_token(head, ptr, \
						search_prev_token(*head, ptr), manager);
		else
		{
			if (ptr->kind == TKN_D_QUOTE)
				ptr->val = expand_env_in_dquote(ptr->val, manager);
			ptr = ptr->next;
		}
	}
}

static void	expansion_helper(t_tree_node *ptr, t_manager *manager)
{
	expansion_token_list(&ptr->init_data.cmd_tokens, manager);
	expansion_token_list(&ptr->init_data.infile_tokens, manager);
	expansion_token_list(&ptr->init_data.outfile_tokens, manager);
	ptr->adv_data.cmd_args = make_cmd_args(ptr->init_data.cmd_tokens);
	ptr->adv_data.infile_paths = make_redir_list(ptr->init_data.infile_tokens);
	ptr->adv_data.outfile_paths = \
		make_redir_list(ptr->init_data.outfile_tokens);
}

void	expansion(t_tree_node *ptr, t_manager *manager)
{
	while (ptr->left != NULL)
		ptr = ptr->left;
	while (ptr != NULL)
	{
		expansion_helper(ptr, manager);
		if (ptr->right != NULL)
			expansion_helper(ptr->right, manager);
		ptr = ptr->prev;
	}
}
