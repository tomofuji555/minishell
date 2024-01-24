/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:19:04 by toshi             #+#    #+#             */
/*   Updated: 2024/01/21 09:28:14 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


void	expansion_tkns(t_token **tkn_head)
{
	t_token *tmp_lst;
	t_token *tkn_ptr;

	tkn_ptr = *tkn_head;
	while(tkn_ptr != NULL)
	{
		if (tkn_ptr->kind == TKN_D_QUOTE)
			tkn_ptr->val = expand_env_in_dquote(tkn_ptr->val);
		if (tkn_ptr->kind == TKN_ENV)
		{
			tmp_lst = expand_env(tkn_ptr);
			if (tmp_lst == NULL) //envの中身がなかったら
			{
				t_token *prev_tkn = save_prev_tkn(*tkn_head, tkn_ptr);
				if (prev_tkn == NULL) //tkn_ptrが先頭だったら
					*tkn_head = tkn_ptr->next;
				else
					prev_tkn->next = tkn_ptr->next;
				tkn_free(tkn_ptr);
			}
			else //envの中身はあった
			{
				t_token *prev_tkn = save_prev_tkn(*tkn_head, tkn_ptr);
				if (prev_tkn == NULL) //tkn_ptrが先頭だったら
				{
					*tkn_head = tmp_lst;
					// tkn_print_lst(tmp_lst);
					tkn_find_last(tmp_lst)->next = tkn_ptr->next;
				}
				else
				{
					prev_tkn->next = tmp_lst;
					tkn_find_last(tmp_lst)->next = tkn_ptr->next;
				}
				tkn_free(tkn_ptr);
			}
		}
		tkn_ptr = tkn_ptr->next;
	}
}

void	expansion(t_tree_node *ptr)
{
	while(ptr != NULL)
	{
		expansion_tkns(&ptr->init_data.cmd_tokens);
		ptr->exec_data.cmd_args = make_cmd_args(ptr->init_data.cmd_tokens);
		expansion_tkns(&ptr->init_data.infile_tokens);
		ptr->exec_data.infile_paths = redir_make_list(ptr->init_data.infile_tokens);
		expansion_tkns(&ptr->init_data.outfile_tokens);
		ptr->exec_data.outfile_paths = redir_make_list(ptr->init_data.outfile_tokens);
		ptr = ptr->right;
	}
}