/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:19:04 by toshi             #+#    #+#             */
/*   Updated: 2024/04/19 23:49:56 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../utils/utils.h"
#include "../token_tozeki/tokenize.h"

//引数を**型にしないと反映されない
//syntaxは保証されている前提で実装
void	expansion_tkn_list(t_token **tkn_head, t_manager *manager)
{
	t_token *tkn_ptr;

	tkn_ptr = *tkn_head;
	while(tkn_ptr != NULL)
	{
		if (tkn_ptr->kind == TKN_HEREDOC)
			tkn_ptr = find_last_valuable_token(tkn_ptr->next)->next;
		else if (tkn_ptr->kind == TKN_ENV)
			tkn_ptr = expand_env_tkn(tkn_head, tkn_ptr, search_prev_token(*tkn_head, tkn_ptr), manager);
		else
		{
			if (tkn_ptr->kind == TKN_D_QUOTE)
				tkn_ptr->val = expand_env_in_dquote(tkn_ptr->val, manager);
			tkn_ptr = tkn_ptr->next;
		}
	}
}

void	expansion(t_tree_node *ptr, t_manager *manager)
{
	while(ptr != NULL)
	{
		expansion_tkn_list(&ptr->init_data.cmd_tokens, manager);
		expansion_tkn_list(&ptr->init_data.infile_tokens, manager);
		expansion_tkn_list(&ptr->init_data.outfile_tokens, manager);
		ptr->adv_data.cmd_args = make_cmd_args(ptr->init_data.cmd_tokens);
		ptr->adv_data.infile_paths = make_redir_list(ptr->init_data.infile_tokens);
		ptr->adv_data.outfile_paths = make_redir_list(ptr->init_data.outfile_tokens);
		// free_init_data(ptr);
		ptr = ptr->right;
	}
}
