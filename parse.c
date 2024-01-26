/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:44:29 by toshi             #+#    #+#             */
/*   Updated: 2024/01/26 09:56:02 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static t_tree_node	*_find_last_tnode(t_tree_node *head)
{
	t_tree_node *ptr;

	ptr = head;
	while(ptr->right != NULL)
		ptr = ptr->right;
	return (ptr);
}

static void	_add_last_tnode(t_tree_node **head, t_tree_node *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	_find_last_tnode(*head)->right = new;
}

//if (next_tree_nodeのtkn_head == now_tree_nodeのtkn_last)
//	nextをNULLを入れて区切る
static void	_fill_null_last_tkn_of_tnode(t_tree_node *tnode_ptr)
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
static t_tree_node *_make_new_tnode(t_token *tkn_begining, t_token *tkn_ptr)
{
	t_tree_node *new;

	new = (t_tree_node *)ft_xcalloc(1, sizeof(t_tree_node));
	new->init_data.cmd_tokens = tkn_begining;
	return (new);
}

// 次のトークンがPIPEかNULLのとき、または今のトークンがPIPEのとき、ノードを作成
t_tree_node *parse(t_token *tkn_ptr)
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
			new = _make_new_tnode(tkn_begining, tkn_ptr);
			_add_last_tnode(&head, new);
			tkn_begining = tkn_ptr->next;
		}
		tkn_ptr =  tkn_ptr->next;
	}
	_fill_null_last_tkn_of_tnode(head);
	push_to_redir_tkns(head);
	return (head);
}