#include "execute.h"

t_token	*make_new_token(char *start, ssize_t mv_count, int token_kind)
{
	t_token *node;

    node = (t_token *)malloc(sizeof(t_token));
    if (node == NULL)
        return (NULL);
    node->val = ft_substr(start, 0, mv_count);
    if (node->val == NULL)
    {
        free(node);
        return (NULL);
    }
    node->next = NULL;
    node->kind = token_kind;
    return (node);
}

t_token	*lstlast(t_token *lst)
{
	t_token	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current -> next != NULL)
		current = current -> next;
	return (current);
}

void	lst_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst)
	{
		if (*lst)
		{
			last = lstlast(*lst);
			last -> next = new;
		}
		else
			*lst = new;
	}
}