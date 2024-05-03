/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:56:07 by toshi             #+#    #+#             */
/*   Updated: 2024/05/03 12:14:18 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../utils/utils.h"

// 両端のスペーストークンをtrimしたいため、substrする前に位置を動かす
static void	update_first_and_last(t_token **first, t_token **last)
{
	t_token	*old_last;
	t_token	*ptr;

	old_last = *last;
	ptr = *first;
	while (ptr != old_last && ptr->kind == TKN_SPACE)
		ptr = ptr->next;
	*first = ptr;
	while (ptr != old_last)
	{
		if (ptr->kind != TKN_SPACE && ptr->next->kind == TKN_SPACE)
			*last = ptr;
		ptr = ptr->next;
	}		
}

// トークン中のスペーストークンのvalを修正する
// 連続で存在するスペーストークンのvalは" "に圧縮するため、
// 後続のスペーストークンは""に置き換える
static void	compress_space(t_token *ptr, t_token *last)
{
	t_token	*prev;

	prev = NULL;
	while (ptr != last)
	{
		if (ptr->kind == TKN_SPACE)
		{
			free(ptr->val);
			if (prev && prev->kind == TKN_SPACE)
				ptr->val = ft_xstrdup("");
			else
				ptr->val = ft_xstrdup(" ");
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

// lastもredirを指しており、redirより先にトークンがない場合と
// lastまで全てスペーストークンだけの場合、trueを返す
static t_bool	is_no_val(t_token *redir, t_token *last)
{
	t_token	*ptr;

	ptr = redir->next;
	while (ptr != last->next && ptr->kind == TKN_SPACE)
		ptr = ptr->next;
	if (ptr != last->next)
		return (FALSE);
	return (TRUE);
}

static t_redir	*make_new_redir(t_token *redir, t_token *last)
{
	t_redir	*new;
	t_token	*first;

	new = (t_redir *)ft_xmalloc(sizeof(t_redir));
	new->next = NULL;
	new->kind = convert_redir_kind(redir);
	if (is_no_val(redir, last))
	{
		new->val = ft_xstrdup("");
		return (new);
	}
	first = redir->next;
	update_first_and_last(&first, &last);
	compress_space(first, last);
	new->val = substr_from_tkn(first, last);
	return (new);
}

t_redir	*make_redir_list(t_token *tkn_ptr)
{
	t_redir	*head;
	t_redir	*new;
	t_token	*redir;

	if (tkn_ptr == NULL)
		return (NULL);
	head = NULL;
	redir = tkn_ptr;
	while (tkn_ptr != NULL)
	{
		if (tkn_ptr->next == NULL || is_redir_tkn(tkn_ptr->next->kind))
		{
			new = make_new_redir(redir, tkn_ptr);
			add_redir_last(&head, new);
			redir = tkn_ptr->next;
		}
		tkn_ptr = tkn_ptr->next;
	}
	return (head);
}
