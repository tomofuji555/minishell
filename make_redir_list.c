/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:00:37 by tozeki            #+#    #+#             */
/*   Updated: 2023/12/18 21:01:28 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	is_redir_token(int kind)
{
	return (kind == TKN_IN_FILE || kind == TKN_HERE_DOC \
		|| kind == TKN_OUT_FILE || kind == TKN_APPEND_FILE);
}

size_t	strlcpy_from_list(char *dest, t_token *src, size_t n)
{
	size_t	dest_i;
	size_t	val_i;

	dest_i = 0;
	while (dest_i < n && src != NULL)
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

t_redir	*make_redir_node(t_token *start, size_t count, int kind)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(t_redir));
	if (node == NULL)
		;//error
	node->val = (char *)malloc(sizeof(char) * (count + 1));
	if (node->val == NULL)
		;//error
	if (start != NULL)
		strlcpy_from_list(node->val, start, count);
	node->kind = kind;
	node->next = NULL;
	return (node);
}

t_redir	*append_redir_node(t_token *tkn_ptr, t_redir *redir_ptr)
{
	t_token	*tkn_start;
	t_redir	*append_first_node;
	size_t	count;

	tkn_start = tkn_ptr;
	append_first_node = redir_ptr;
	count = 0;
	while (tkn_ptr != NULL)
	{
		count += ft_strlen(tkn_ptr->val);
		if (tkn_ptr->next == NULL || is_redir_token(tkn_ptr->next->kind))
		{
			redir_ptr->next = make_redir_node(tkn_start, count, \
				tkn_start->kind);
			if (redir_ptr->next == NULL)
				;//error
			redir_ptr = redir_ptr->next;
			tkn_start = tkn_ptr;
			count = 0;
		}
		tkn_ptr = tkn_ptr->next;
	}
	return (append_first_node);
}

t_redir	*make_redir_list(t_token *tkns_head)
{
	t_redir	*redir_head;

	if (tkns_head == NULL)
		return (NULL);
	redir_head = make_redir_node(NULL, 0, TKN_HEAD);
	if (redir_head == NULL)
		;//error
	redir_head->next = append_redir_node(tkns_head->next, redir_head);
	if (redir_head->next == NULL)
		;//error
	return (redir_head);
}
