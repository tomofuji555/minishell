/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:44:29 by toshi             #+#    #+#             */
/*   Updated: 2024/02/15 16:37:44 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	add_redir_tkns_last(t_token **to_head, t_token *prev_of_first, t_token **from_head)
{
	t_token *first;
	
	if (prev_of_first == NULL)
	{
		first = *from_head;
		*from_head = find_last_valuable_tkn(first->next)->next;
	}
	else
	{
		first = prev_of_first->next;
		prev_of_first->next = find_last_valuable_tkn(first->next)->next;
	}
	if (*to_head == NULL)
		*to_head = first;
	else
		find_last_tkn(*to_head)->next = first;
	find_last_valuable_tkn(first->next)->next = NULL;
}

//init_data.cmd_tknsからリダイレクト対象のnodeをredir_tkns_headにpushする
static t_token *separate_and_make_redir_tkns_lst\
	(t_token **head, t_bool (*is_func)(enum e_token_kind))
{
	t_token *redir_tkns_head;
	t_token *prev;
	t_token *ptr;
	t_token *next;

	redir_tkns_head = NULL;
	ptr = *head;
	prev = NULL;
	while(ptr != NULL)
	{
		if (is_func(ptr->kind))
		{
			next = find_last_valuable_tkn(ptr->next)->next;
			add_redir_tkns_last(&redir_tkns_head, prev, head);
			prev = save_prev_tkn(*head, next);
			ptr = next;
		}
		else
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}
	return (redir_tkns_head);
}

static void	push_to_redir_tkns(t_tree_node *tnode_head)
{
	t_tree_node *tnode_ptr;
	
	tnode_ptr = tnode_head;
	while(tnode_ptr != NULL)
	{
		tnode_ptr->init_data.infile_tokens = separate_and_make_redir_tkns_lst\
			(&tnode_ptr->init_data.cmd_tokens, is_in_redir_tkn);
		tnode_ptr->init_data.outfile_tokens = separate_and_make_redir_tkns_lst\
			(&tnode_ptr->init_data.cmd_tokens, is_out_redir_tkn);
		tnode_ptr = tnode_ptr->right;
	}
}

//if (next_tree_nodeのtkn_head == now_tree_nodeのtkn_last)
//	nextをNULLを入れて区切る
static void	fill_null_last_tkn_of_tnode(t_tree_node *tnode_ptr)
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

static t_tree_node	*find_last_tnode(t_tree_node *head)
{
	t_tree_node *ptr;

	ptr = head;
	while(ptr->right != NULL)
		ptr = ptr->right;
	return (ptr);
}

static void	add_tnode_last(t_tree_node **head, t_tree_node *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_tnode(*head)->right = new;
}

//tree_nodeのlast_tkn->nextにNULLを入れない。後々処理する
static t_tree_node *make_new_tnode(t_token *tkn_begining, t_token *tkn_ptr)
{
	t_tree_node *new;

	new = (t_tree_node *)ft_xcalloc(1, sizeof(t_tree_node));
	new->init_data.cmd_tokens = tkn_begining;
	return (new);
}

//redir_tknの次がNULLじゃない前提で実装している
void	remove_space_afrer_redir(t_token **tkn_head)
{
	t_token *prev;
	t_token *ptr;

	prev = NULL;
	ptr = *tkn_head;
	while(ptr != NULL)
	{
		if (prev != NULL && is_redir_tkn(prev->kind) && ptr->kind == TKN_SPACE)
			remove_tkn(tkn_head, ptr, prev);
		prev = ptr;
		ptr = ptr->next;
	}
}

// 次のトークンがPIPEかNULLのとき、または今のトークンがPIPEのとき、ノードを作成
t_tree_node *parse(t_token *tkn_ptr)
{
	t_token		*tkn_begining;
	t_tree_node *head;
	t_tree_node *new;
	
	remove_space_afrer_redir(&tkn_ptr);
	head = NULL;
	tkn_begining = tkn_ptr;
	while(tkn_ptr != NULL)
	{
		if (tkn_ptr->kind == TKN_PIPE ||\
			tkn_ptr->next == NULL || tkn_ptr->next->kind == TKN_PIPE)
		{
			new = make_new_tnode(tkn_begining, tkn_ptr);
			add_tnode_last(&head, new);
			tkn_begining = tkn_ptr->next;
		}
		tkn_ptr =  tkn_ptr->next;
	}
	fill_null_last_tkn_of_tnode(head);
	push_to_redir_tkns(head);
	return (head);
}
