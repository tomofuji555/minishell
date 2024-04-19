/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tnode_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 00:47:11 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 00:48:03 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"

static t_tree_node	*_find_last_tnode(t_tree_node *head)
{
	t_tree_node *ptr;

	ptr = head;
	while(ptr->right != NULL)
		ptr = ptr->right;
	return (ptr);
}

static void	_add_tnode_last(t_tree_node **head, t_tree_node *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	_find_last_tnode(*head)->right = new;
}

//tree_nodeのlast_tkn->nextにNULLを入れない。後々処理する
static t_tree_node *_make_new_tnode(t_token *tkn_begining)
{
	t_tree_node *new;

	new = (t_tree_node *)ft_xcalloc(1, sizeof(t_tree_node));
	new->init_data.cmd_tokens = tkn_begining;
	return (new);
}


// 次のトークンがPIPEかNULLのとき、または今のトークンがPIPEのとき、ノードを作成
t_tree_node *make_tnode_list(t_token *tkn_ptr)
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
			new = _make_new_tnode(tkn_begining);
			_add_tnode_last(&head, new);
			tkn_begining = tkn_ptr->next;
		}
		tkn_ptr =  tkn_ptr->next;
	}
	return (head);
}