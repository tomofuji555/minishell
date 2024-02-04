/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:00:37 by tozeki            #+#    #+#             */
/*   Updated: 2024/02/02 21:34:38 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_redir	*_redir_find_last(t_redir *head)
{
	t_redir	*ptr;

	ptr = head;
	while(ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	_redir_add_last(t_redir **head_node, t_redir *new_node)
{
	if (*head_node == NULL)
	{
		*head_node = new_node;
		return;
	}
	_redir_find_last(*head_node)->next = new_node;
}


static t_bool	_contains_quote_tkn(t_token *begining)
{
	t_token *ptr;

	ptr = begining->next;
	while (ptr && !is_redir_token(ptr->kind)) //is_valuable_tkn()でもアリ
	{
		if (ptr->kind == TKN_S_QUOTE || ptr->kind == TKN_D_QUOTE)
			return (TRUE);
		ptr = ptr->next;
	}
	return (FALSE);
}

static enum e_redir_kind	_convert_redir_kind(t_token *begining)
{
	if (begining->kind == TKN_IN_FILE)
		return (REDIR_IN_FILE);
	else if (begining->kind == TKN_HEREDOC)
	{
		if (_contains_quote_tkn(begining))
			return (REDIR_HEREDOC_NO_EXPAND);
		else
			return (REDIR_HEREDOC);
	}
	else if (begining->kind == TKN_OUT_FILE)
		return (REDIR_OUT_FILE);
	else
		return (REDIR_APPEND_FILE);
}

//リダイレクトのvalがifsのみだと、空文字列("")が入る
t_redir	*_redir_make_new(t_token *begining, t_token *last)
{
	t_redir	*node;
	char *tmp_val;

	node = (t_redir *)ft_xmalloc(sizeof(t_redir));
	tmp_val =  substr_from_tkn(begining->next, last);
	node->val =  ft_xstrtrim(tmp_val, " \t\n");
	free(tmp_val);
	node->kind = _convert_redir_kind(begining);
	node->next = NULL;
	return (node);
}

t_redir	*redir_make_lst(t_token *tkn_ptr)
{
	t_redir	*head;
	t_redir *new;
	t_token	*tkn_begining;

	if (tkn_ptr == NULL)
		return (NULL);
	head = NULL;
	tkn_begining = tkn_ptr;
	while (tkn_ptr != NULL)
	{
		if (tkn_ptr->next == NULL || is_redir_token(tkn_ptr->next->kind))
		{
			new = _redir_make_new(tkn_begining, tkn_ptr);
			_redir_add_last(&head, new);
			tkn_begining = tkn_ptr->next;
		}
		tkn_ptr = tkn_ptr->next;
	}
	return (head);
}
