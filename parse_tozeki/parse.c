/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:44:29 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 00:51:32 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"

//redir_tknの次がNULLじゃない前提で実装している
static void	_del_space_afrer_redir(t_token **tkn_head)
{
	t_token *prev;
	t_token *ptr;

	prev = NULL;
	ptr = *tkn_head;
	while(ptr != NULL)
	{
		if (prev != NULL && is_redir_tkn(prev->kind) && ptr->kind == TKN_SPACE)
			remove_token(tkn_head, ptr, prev);
		prev = ptr;
		ptr = ptr->next;
	}
}

//if (next_tree_nodeのtkn_head == now_tree_nodeのtkn_last)
//	nextをNULLを入れて区切る
static void	_split_last_tkn(t_tree_node *tnode_ptr)
{
	t_token *tkn_ptr;
	t_token *tkn_next_head;

	while(tnode_ptr->right != NULL)
	{	
		tkn_ptr = tnode_ptr->init_data.cmd_tokens;
		tkn_next_head = tnode_ptr->right->init_data.cmd_tokens;
		while(tkn_ptr->next != tkn_next_head)
			tkn_ptr = tkn_ptr->next;
		tkn_ptr->next = NULL;
		tnode_ptr = tnode_ptr->right;
	}
}

t_tree_node *parse(t_token *head)
{
	t_tree_node *tnode_list;

	_del_space_afrer_redir(&head);
	tnode_list = make_tnode_list(head);
	_split_last_tkn(tnode_list);
	move_to_redir_tokens(tnode_list);
	return tnode_list;
}