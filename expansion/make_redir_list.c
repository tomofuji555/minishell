/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:56:07 by toshi             #+#    #+#             */
/*   Updated: 2024/04/30 19:31:30 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../utils/utils.h"

// 両端のスペーストークンをtrimしたいため、substrする前に位置を動かす
// firstからlastまでスペーストークンしかないのなら、firstはlastのスペーストークンまで
// 移動する
static void	update_first_and_last(t_token **first, t_token **last)
{
	t_token *old_last;
	t_token *ptr;

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
static void	compress_space(t_token *first, t_token *last)
{
	t_token	*prev;
	t_token	*ptr;

	if (first == last && first->kind == TKN_SPACE)
	{
		free(first->val);
		first->val = ft_xstrdup("");
		return ;
	}
	ptr = first;
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

// (redir==last)は、リダイレクトしかトークンがない時
static t_redir	*make_new_redir(t_token *redir, t_token *last)
{
	t_redir	*new;
	t_token	*first;

	new = (t_redir *)ft_xmalloc(sizeof(t_redir));
	new->next = NULL;
	new->kind = convert_redir_kind(redir);
	if (redir == last)
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
