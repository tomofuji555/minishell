#include "../execute.h"

t_redir	*make_redir_list_ver2(t_token *tkn_ptr)
{
	t_redir	*redir_list;
	t_redir	*redir_ptr;
	t_token	*tkn_first;

	if (tkn_ptr == NULL)
		return (NULL);
	tkn_first = tkn_ptr;
	redir_list = make_redir_node(tkn_first, tkn_ptr);
	if (redir_list == NULL)
		return (NULL);
	redir_ptr = redir_list;
	while (tkn_ptr != NULL)
	{
		if (tkn_ptr->next == NULL || is_redir_tkn(tkn_ptr->next->kind))
		{
			redir_ptr->next = make_redir_node(tkn_first, tkn_ptr);
			if (redir_ptr->next == NULL)
				;//error
			redir_ptr = redir_ptr->next;
			tkn_first = tkn_ptr->next;
		}
		tkn_ptr = tkn_ptr->next;
	}
	return (redir_list);
}