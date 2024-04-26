/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:56:07 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 19:13:23 by tozeki           ###   ########.fr       */
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

//リダイレクトのvalがifsのみだと、空文字列("")が入る
static t_redir	*make_new_redir(t_token *first, t_token *last)
{
	t_redir	*node;
	char	*tmp_val;

	node = (t_redir *)ft_xmalloc(sizeof(t_redir));
	node->kind = convert_redir_kind(first);
	tmp_val = substr_from_tkn(first->next, last);
	node->val = ft_xstrtrim(tmp_val, " \t\n");
	free(tmp_val);
	node->next = NULL;
	return (node);
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
