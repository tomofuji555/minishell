#include "execute.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	is_redir_token(int 	kind)
{
	return (kind == TKN_IN_FILE || kind == TKN_HERE_DOC 
		|| kind == TKN_OUT_FILE || kind == TKN_APPEND_FILE);
}

size_t strlcpy_from_list(char *dest, t_token *src, size_t n)
{
	size_t	dest_i;
	size_t	src_i;

	dest_i = 0;
	while(dest_i < n && src != NULL)
	{
		src_i = 0;
		while (src->val[src_i] != '\0')
		{
			dest[dest_i] = src->val[src_i];
			dest_i++;
			src_i++;
		}
		src = src->next;
	}
	dest[dest_i] = '\0';
	return (dest_i);
}

t_redir *make_redir_node(t_token *start, size_t count, int kind)
{
	t_redir *node;

	node = (t_redir *)malloc(sizeof(t_redir));
	if (node == NULL)
		;//error
	node->val = (char *)malloc(sizeof(char) * (count + 1));
	if (node->val == NULL)
		;//error
	if (strlcpy_from_list(node->val, start, count) != count)
		;//error
	node->kind = kind;
	node->next = NULL;
	return (node);
}

t_redir *make_redir_list(t_token *tkns_head)
{
	t_token	*tkn_start;
	t_token	*tkn_ptr;
	size_t	count;
	t_redir	*redir_head;
	t_redir	*redir_ptr;

	tkn_start = tkns_head->next;
	tkn_ptr = tkn_start->next;
	redir_head = make_redir_node(tkn_start, 0, TKN_SPACE);
	if (redir_head == NULL)
		;//error
	redir_ptr = redir_head;
	count = 0;
	while(tkn_ptr != NULL)
	{
		if (is_redir_token(tkn_ptr->kind))
		{
			redir_ptr->next = make_redir_node(tkn_start, count, tkn_start->kind);
			if (redir_ptr->next == NULL)
				;//error
			redir_ptr = redir_ptr->next;
			tkn_start = tkn_ptr;
			count = 0;
		}
		else
			count += ft_strlen(tkn_ptr->val);
		tkn_ptr = tkn_ptr->next;
	}
	redir_ptr->next = make_redir_node(tkn_start, count, tkn_start->kind);
	return (redir_head);
}