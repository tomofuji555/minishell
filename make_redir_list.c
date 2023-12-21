/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:00:37 by tozeki            #+#    #+#             */
/*   Updated: 2023/12/20 15:03:55 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	_is_redir_token(int kind)
{
	return (kind == TKN_IN_FILE || kind == TKN_HERE_DOC \
		|| kind == TKN_OUT_FILE || kind == TKN_APPEND_FILE);
}
size_t	strlen_of_list_untill_last(t_token *begining, t_token *last)
{
	t_token	*ptr;
	size_t	i;

	ptr = begining;
	i = 0;
	while(ptr != last->next)
	{
		while(ptr->val[i] != '\0')
			i++; 
		ptr = ptr->next;
	}
	return (i);
}

size_t	strlcpy_from_list(char *dest, t_token *src, size_t len)
{
	size_t	dest_i;
	size_t	val_i;

	dest_i = 0;
	while (dest_i + 1 < len && src != NULL)
	{
		val_i = 0;
		while (src->val[val_i] != '\0')
		{
			dest[dest_i] = src->val[val_i];
			dest_i++;
			val_i++;
		}
		src = src->next;
	}
	dest[dest_i] = '\0';
	return (dest_i);
}

enum e_redir_kind	convert_redir_kind(enum e_token_kind token_kind)
{
	if (token_kind == TKN_IN_FILE)
		return (REDIR_IN_FILE);
	else if (token_kind == TKN_HERE_DOC)
		return (REDIR_HERE_DOC);
	else if (token_kind == TKN_OUT_FILE)
		return (REDIR_OUT_FILE);
	else if (token_kind == TKN_APPEND_FILE)
		return (REDIR_APPEND_FILE);
	else
		return (-1);
}

t_redir	*make_redir_node(t_token *begining, t_token *last)
{
	t_redir	*node;
	size_t	len;

	node = (t_redir *)malloc(sizeof(t_redir));
	if (node == NULL)
		return (NULL);
	len = strlen_of_list_untill_last(begining, last) + 1;
	node->val = (char *)malloc(sizeof(char) * len);
	if (node->val == NULL)
		;//error
	strlcpy_from_list(node->val, begining, len);
	node->kind = convert_redir_kind(begining->kind);
	node->next = NULL;
	return (node);
}


t_redir	*find_last_node(t_redir *first)
{
	t_redir	*ptr;

	ptr = first;
	while(ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	reidr_add_node_last(t_redir **first_node, t_redir *new_node)
{
	t_redir *last_node;

	last_node = find_last_node(*first_node);
	if (last_node == *first_node)
	{
		*first_node = new_node;
		return;
	}
	last_node->next = new_node;
}

t_redir	*make_redir_list(t_token *tkn_ptr)
{
	t_redir	*redir_first;
	t_token	*tkn_begining;
	t_redir *redir_new_node;

	if (tkn_ptr == NULL)
		return (NULL);
	redir_first = NULL;
	tkn_begining = tkn_ptr;
	while (tkn_ptr != NULL)
	{
		if (tkn_ptr->next == NULL || is_redir_token(tkn_ptr->next->kind))
		{
			redir_new_node = make_redir_node(tkn_begining, tkn_ptr);
			if (redir_new_node == NULL)
				;//error
			add_node_last(&redir_first, redir_new_node);
			tkn_begining = tkn_ptr->next;
		}
		tkn_ptr = tkn_ptr->next;
	}
	return (redir_first);
}









