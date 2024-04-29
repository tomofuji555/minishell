/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:56:07 by toshi             #+#    #+#             */
/*   Updated: 2024/04/29 16:15:55 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../utils/utils.h"

static t_redir	*find_last_redir(t_redir *ptr)
{
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

static void	add_redir_last(t_redir **head, t_redir *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_redir(*head)->next = new;
}

// static	t_token *find_new_last(t_token *redir, t_token *last, enum e_token_kind kind)
// {
// 	t_token *ptr;
// 	t_token *last_ptr;

// 	last_ptr = last;
// 	ptr = redir->next;
// 	while (ptr != last)
// 	{
// 		if (ptr->kind != kind && ptr->next && ptr->next->kind == kind)
// 			last_ptr = ptr;
// 		ptr = ptr->next;
// 	}
// 	return (last_ptr);
// 	//if (!last_ptr)
// 	//	return ;
// 	//ptr = last_ptr;
// 	//while (ptr != last)
// 	//{
// 	//	remove
// 	//}
// }

// static	t_token *find_new_last(t_token *redir, t_token *last, enum e_token_kind kind)
// {
// 	t_token *ptr;
// 	t_token *next;

// 	ptr = redir->next;
// 	while (ptr->kind == TKN_SPACE)
// 		ptr = ptr->next;
// 	return (ptr);
// }

// static	t_token *trim_tokens(t_token *first, t_token *last, enum e_token_kind kind)
// {
// 	t_token *next_ptr;
// 	t_token *last_ptr;
// 	t_token *ptr;

// 	ptr = first->next;
// 	while (ptr != last && ptr->kind == kind)
// 	{
// 		next_ptr = ptr->next;
// 		remove_token(&first, ptr, search_prev_token(first, ptr));
// 		ptr = next_ptr;
// 	}
// 	while (ptr != last)
// 	{
// 		if (ptr->kind != kind && ptr->next && ptr->next->kind == kind)
// 			last_ptr = ptr;
// 		ptr = ptr->next;
// 	}
	
// }

// //first(redidr_tkn)の次には必ず何かのトークンが入っているのが前提で作成
// static void	trim_and_compress_space(t_token *redir, t_token *last)
// {
// 	t_token *next_redir_first;
// 	t_token *new_last;
// 	t_token *new_first;
// 	t_token *ptr;
// 	t_token *prev;
// 	t_token *next;

// 	next_redir_first = last->next;
// 	new_first = find_new_first();
// 	new_last = find_new_last(redir, last, TKN_SPACE);
// 	ptr = redir->next;
// 	prev = redir;
// 	while (ptr != new_first)
// 	{
// 		next = ptr->next;
// 		remove_token(redir, ptr, prev);
// 		prev = ptr;
// 		ptr = next;
// 	}
// 	ptr = new_last


// }

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
	if (ptr == last && ptr->kind == TKN_SPACE)
	{
		free(ptr->val);
		ptr->val = ft_xstrdup("");
	}
}

// リダイレクトのvalがifsのみだと、空文字列("")が入る->trim適用時なら
static t_redir	*make_new_redir(t_token *redir, t_token *last)
{
	t_redir	*new;
	t_token	*first;

	
	new = (t_redir *)ft_xmalloc(sizeof(t_redir));
	new->kind = convert_redir_kind(redir);
	new->next = NULL;
	first = redir->next;
	if (first == NULL || is_redir_tkn(first->kind))
	{
		new->val = ft_xstrdup("");
		return (new);
	}
	wc(NULL);
	//set関数
	update_first_and_last(&first, &last);
	// //compress関数
	compress_space(first, last);
	new->val = substr_from_tkn(first, last);
	return (new);
}

t_redir	*make_redir_list(t_token *tkn_ptr)
{
	t_redir	*head;
	t_redir	*new;
	t_token	*tkn_first;

	if (tkn_ptr == NULL)
		return (NULL);
	head = NULL;
	tkn_first = tkn_ptr;
	while (tkn_ptr != NULL)
	{
		if (tkn_ptr->next == NULL || is_redir_tkn(tkn_ptr->next->kind))
		{
			new = make_new_redir(tkn_first, tkn_ptr);
			add_redir_last(&head, new);
			tkn_first = tkn_ptr->next;
		}
		tkn_ptr = tkn_ptr->next;
	}
	return (head);
}
