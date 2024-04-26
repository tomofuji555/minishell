/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to_redir_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 00:50:48 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 19:21:19 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"

/// @brief リダイレクトとそのvalueのtoken列をリダイレクト専用のリストのheadに送る。
/// last->nextがNULL埋めされるため、next_ptrは事前に持つ。
/// @param redir_tkn_head 送り先のリダイレクト用tokenリストのhead
/// @param cmd_tkn_head 送り元のコマンド用tokenリストのhead
/// @param first 送る最初のtoken。first->nextがNULLでないことは事前のsyntax_error_checkで補償されている
/// @return 送ったtoken列の次のtoken_ptrを送る
static t_token	*separate_and_append_redir_tokens(t_token **redir_tkn_head, \
	t_token **cmd_tkn_head, t_token *first)
{
	t_token	*last;
	t_token	*next_ptr;
	t_token	*prev;

	last = find_last_valuable_token(first->next);
	next_ptr = last->next;
	if (*redir_tkn_head == NULL)
		*redir_tkn_head = first;
	else
		find_last_token(*redir_tkn_head)->next = first;
	last->next = NULL;
	prev = search_prev_token(*cmd_tkn_head, first);
	if (prev == NULL)
		*cmd_tkn_head = next_ptr;
	else
		prev->next = next_ptr;
	return (next_ptr);
}

//init_data.cmd_tokensからリダイレクト対象のnodeをredir_tkn_headにpushする
static t_token	*make_redir_tokens_list(t_token **cmd_tkn_head, \
	t_bool (*is_redir_func)(enum e_token_kind))
{
	t_token	*redir_tkn_head;
	t_token	*ptr;

	redir_tkn_head = NULL;
	ptr = *cmd_tkn_head;
	while (ptr != NULL)
	{
		if (is_redir_func(ptr->kind))
			ptr = separate_and_append_redir_tokens(&redir_tkn_head, \
				cmd_tkn_head, ptr);
		else
			ptr = ptr->next;
	}
	return (redir_tkn_head);
}

static void	move_to_redir_tokens_helper(t_tree_node *ptr)
{
	ptr->init_data.infile_tokens = \
		make_redir_tokens_list(&ptr->init_data.cmd_tokens, is_in_redir_tkn);
	ptr->init_data.outfile_tokens = \
		make_redir_tokens_list(&ptr->init_data.cmd_tokens, is_out_redir_tkn);
}

void	move_to_redir_tokens(t_tree_node *ptr)
{
	while (ptr->left != NULL)
		ptr = ptr->left;
	move_to_redir_tokens_helper(ptr);
	while (ptr != NULL)
	{
		if (ptr->right != NULL)
			move_to_redir_tokens_helper(ptr->right);
		ptr = ptr->prev;
	}
}
