/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:07:59 by toshi             #+#    #+#             */
/*   Updated: 2024/01/26 10:16:40 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//save_last~系は必ずptr->next!=NULLで止める
t_token *save_redir_tkn_last(t_token *tkn_ptr)
{
	tkn_ptr = tkn_ptr->next;
	while(tkn_ptr->kind == TKN_SPACE)
		tkn_ptr = tkn_ptr->next;
	while(tkn_ptr->next != NULL && is_valuable_token(tkn_ptr->next->kind))
		tkn_ptr = tkn_ptr->next;
	return (tkn_ptr);
}

static void	_add_redir_tkns_last(t_token **head, t_token *prev_of_first, t_token *last)
{
	if (*head == NULL)
		*head = prev_of_first->next;
	else
		find_last_tkn(*head)->next = prev_of_first->next;
	prev_of_first->next = last->next;
	last->next = NULL;
}

//init_data.cmd_tknsからリダイレクト対象のnodeをredir_tkns_headにpushする
t_token *separate_and_make_redir_tkns_lst\
	(t_token *ptr, t_bool (*is_func)(enum e_token_kind))
{
	t_token *redir_tkns_head;
	t_token *last;

	redir_tkns_head = NULL;
	while(ptr != NULL)
	{
		if (ptr->next != NULL && is_func(ptr->next->kind))
		{
			last = save_redir_tkn_last(ptr->next);
			_add_redir_tkns_last(&redir_tkns_head, ptr, last);
		}
		ptr = ptr->next;
	}
	return (redir_tkns_head);
}

void	push_to_redir_tkns(t_tree_node *tnode_ptr)
{
	while(tnode_ptr != NULL)
	{
		tnode_ptr->init_data.infile_tokens = separate_and_make_redir_tkns_lst\
			(tnode_ptr->init_data.cmd_tokens, is_in_redir_tkn);
		tnode_ptr->init_data.outfile_tokens = separate_and_make_redir_tkns_lst\
			(tnode_ptr->init_data.cmd_tokens, is_out_redir_tkn);
		tnode_ptr = tnode_ptr->right;
	}
}