/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:44:29 by toshi             #+#    #+#             */
/*   Updated: 2024/01/17 19:53:21 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//if (next_tree_nodeのtkn_head == now_tree_nodeのtkn_last)
//	nextをNULLを入れて区切る
static void	_separate_tkn_last(t_tree_node *tnode_ptr)
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

//tree_nodeのlast_tkn->nextにNULLを入れない。後々処理する
static t_tree_node *_tnode_make_new(t_token *tkn_begining, t_token *tkn_ptr)
{
	t_tree_node *new;

	new = (t_tree_node *)ft_xcalloc(1, sizeof(t_tree_node));
	new->init_data.cmd_tokens = tkn_begining;
	return (new);
}

// 次のトークンがPIPEかNULLのとき、または今のトークンがPIPEのとき、ノードを作成
t_tree_node	*make_tree_lst(t_token *tkn_ptr)
{
	t_token		*tkn_begining;
	t_tree_node *head;
	t_tree_node *new;
	
	head = NULL;
	tkn_begining = tkn_ptr;
	while(tkn_ptr != NULL)
	{
		if (tkn_ptr->kind == TKN_PIPE ||\
			tkn_ptr->next == NULL || tkn_ptr->next->kind == TKN_PIPE)
		{
			new = _tnode_make_new(tkn_begining, tkn_ptr);
			tnode_add_last_right(&head, new);
			tkn_begining = tkn_ptr->next;
		}
		tkn_ptr =  tkn_ptr->next;
	}
	_separate_tkn_last(head);
	return (head);
}

//問題あり。返り値を変数に代入すると反映されない。アローがあるかないかの違い。
void	push_all_redir_tkns(t_tree_node *tnode_ptr)
{
	t_token *infile_tokens;
	t_token *outfile_tokens;
	t_token *cmd_tokens;

	
	while(tnode_ptr != NULL)
	{
		infile_tokens = tnode_ptr->init_data.infile_tokens;
		outfile_tokens = tnode_ptr->init_data.outfile_tokens;
		cmd_tokens = tnode_ptr->init_data.cmd_tokens;
		tnode_ptr->init_data.infile_tokens = push_redir_tkns(cmd_tokens, is_in_redir_tkn);
		tnode_ptr->init_data.outfile_tokens = push_redir_tkns(cmd_tokens, is_out_redir_tkn);
		tnode_ptr = tnode_ptr->right;
	}
}

t_tree_node *parse(t_token *tkn_head)
{
	t_tree_node *tnode_head;

	tnode_head = make_tree_lst(tkn_head);
	push_all_redir_tkns(tnode_head);
	return (tnode_head);
}