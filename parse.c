/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:44:29 by toshi             #+#    #+#             */
/*   Updated: 2024/04/08 23:02:35 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//redir_tknの次がNULLじゃない前提で実装している
static void	del_space_afrer_redir(t_token **tkn_head)
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
			

/// @brief リダイレクトとそのvalueのtoken列をリダイレクト専用のリストのheadに送る。
/// last->nextがNULL埋めされるため、next_ptrは事前に持つ。
/// @param redir_tkns_head 送り先のリダイレクト用tokenリストのhead
/// @param cmd_tkns_head 送り元のコマンド用tokenリストのhead
/// @param first 送る最初のtoken。first->nextがNULLでないことは事前のsyntax_error_checkで補償されている
/// @return 送ったtoken列の次のtoken_ptrを送る
t_token	*separate_and_append_redir_tkns(t_token **redir_tkns_head, t_token **cmd_tkns_head, t_token *first)
{
	t_token *last;
	t_token *next_ptr;
	t_token *prev;

	last = find_last_valuable_tkn(first->next);
	next_ptr = last->next;
	if (*redir_tkns_head == NULL)
		*redir_tkns_head = first;
	else
		find_last_tkn(*redir_tkns_head)->next = first;
	last->next = NULL;
	prev = search_prev_tkn(*cmd_tkns_head, first);
	if (prev == NULL)
		*cmd_tkns_head = next_ptr;
	else
		prev->next = next_ptr;
	return (next_ptr);
}

//init_data.cmd_tknsからリダイレクト対象のnodeをredir_tkns_headにpushする
static t_token *make_redir_tkns_list(t_token **cmd_tkns_head, t_bool (*is_func)(enum e_token_kind))
{
	t_token *redir_tkns_head;
	t_token *ptr;

	redir_tkns_head = NULL;
	ptr = *cmd_tkns_head;
	while (ptr != NULL)
	{
		if (is_func(ptr->kind))
			ptr = separate_and_append_redir_tkns(&redir_tkns_head, cmd_tkns_head, ptr);
		else
			ptr = ptr->next;
	}
	return (redir_tkns_head);
}

static void	move_to_redir_tkns(t_tree_node *tnode_head)
{
	t_tree_node *tnode_ptr;
	
	tnode_ptr = tnode_head;
	while(tnode_ptr != NULL)
	{
		tnode_ptr->init_data.infile_tokens = make_redir_tkns_list\
			(&tnode_ptr->init_data.cmd_tokens, is_in_redir_tkn);
		tnode_ptr->init_data.outfile_tokens = make_redir_tkns_list\
			(&tnode_ptr->init_data.cmd_tokens, is_out_redir_tkn);
		tnode_ptr = tnode_ptr->right;
	}
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

//if (next_tree_nodeのtkn_head == now_tree_nodeのtkn_last)
//	nextをNULLを入れて区切る
static void	split_last_tkn(t_tree_node *tnode_ptr)
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
static t_tree_node *make_new_tnode(t_token *tkn_begining)
{
	t_tree_node *new;

	new = (t_tree_node *)ft_xcalloc(1, sizeof(t_tree_node));
	new->init_data.cmd_tokens = tkn_begining;
	return (new);
}


// 次のトークンがPIPEかNULLのとき、または今のトークンがPIPEのとき、ノードを作成
static t_tree_node *make_tnode_list(t_token *tkn_ptr)
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
			new = make_new_tnode(tkn_begining);
			add_tnode_last(&head, new);
			tkn_begining = tkn_ptr->next;
		}
		tkn_ptr =  tkn_ptr->next;
	}
	return (head);
}

/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

t_tree_node *parse(t_token *head)
{
	t_tree_node *tnode_list;

	del_space_afrer_redir(&head);
	tnode_list = make_tnode_list(head);
	split_last_tkn(tnode_list);
	move_to_redir_tkns(tnode_list);
	return tnode_list;
}