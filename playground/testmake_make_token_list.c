#include "execute.h"

t_token *make_token_node(char *str, enum e_token_kind kind)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	new->val = str; //strがfreeされるとエラーになる
	new->kind = kind;
	new->next = NULL;
	return (new);
}

t_token *find_last_node(t_token *head)
{
	t_token *ptr;

	ptr = head;
	while(ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void add_node_last(t_token **head, t_token *new)
{
	t_token *last_node;

	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		last_node = find_last_node(*head);
		last_node->next = new;
	}
}

t_token	*test_make_token_list(char *strs[], enum e_token_kind kinds[])
{
	int i;
	t_token *head;
	t_token *new;

	i = 0;
	head = NULL;
	while(strs[i] != NULL)
	{
		new = make_token_node(strs[i], kinds[i]);
		add_node_last(&head, new);
		i++;
	}
	return (head);
}



// int main()
// {
// 	char *strs[]			=	{
// 								">",
// 								"aaa",
// 								"ABC",
// 								">>",
// 								"ABC",
// 								"hij",
// 								NULL
// 								};
// 	enum e_token_kind kinds[]	=	{
// 								TKN_OUT_FILE,
// 								TKN_TEXT,
// 								TKN_ENV,
// 								TKN_APPEND_FILE,
// 								TKN_ENV,
// 								TKN_TEXT
// 								};
// 	t_token *redir_tokens = test_make_token_list(strs, kinds);
// 	print_token_list(redir_tokens);
	
// }





