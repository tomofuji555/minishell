/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:19:04 by toshi             #+#    #+#             */
/*   Updated: 2024/01/26 13:28:05 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


void	expansion_tkn_lst(t_token *tkn_head)
{
	t_token *tkn_ptr;

	tkn_ptr = tkn_head;
	while(tkn_ptr != NULL)
	{
		if (tkn_ptr->kind == TKN_HEREDOC)
			tkn_ptr = save_redir_tkn_last(tkn_ptr);
		else if (tkn_ptr->kind == TKN_D_QUOTE)
			tkn_ptr->val = expand_env_in_dquote(tkn_ptr->val);
		else if (tkn_ptr->kind == TKN_ENV)
			expand_env_of_tkn(&tkn_head, tkn_ptr, save_prev_tkn(tkn_head, tkn_ptr));
		tkn_ptr = tkn_ptr->next;
	}
}

void	expansion(t_tree_node *ptr)
{
	while(ptr != NULL)
	{
		expansion_tkn_lst(ptr->init_data.cmd_tokens);
		expansion_tkn_lst(ptr->init_data.infile_tokens);
		expansion_tkn_lst(ptr->init_data.outfile_tokens);
		// ptr->exec_data.cmd_args = make_cmd_args(ptr->init_data.cmd_tokens);
		// ptr->exec_data.infile_paths = redir_make_list(ptr->init_data.infile_tokens);
		// ptr->exec_data.outfile_paths = redir_make_list(ptr->init_data.outfile_tokens);
		ptr = ptr->right;
	}
}