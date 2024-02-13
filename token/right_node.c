#include "minishell.h"

t_token	*rs_append_node_and_add_null(t_token **head, t_token *last_pipe)
{
	t_token	*rs_of_pipe;
	t_token	*first_head;
	t_token	*first_rs_of_pipe;

	first_head = *head;
	rs_of_pipe = last_pipe->next;
	first_rs_of_pipe = rs_of_pipe;
	while (rs_of_pipe->next != NULL)
		rs_of_pipe = rs_of_pipe->next;
	*head = last_pipe;
	(*head)->next = NULL;
	*head = first_head;
	rs_of_pipe->next = NULL;
	rs_of_pipe = first_rs_of_pipe;
	return (rs_of_pipe);
}

t_token	*cmd_of_rs(t_token **head, t_token *last_pipe, bool is_first)
{
	t_token	*rs_token_node;
	t_token	*first_head;

	first_head = *head;
	if (is_first == 0)
		rs_token_node = rs_append_node_and_add_null (head, last_pipe);
	else
	{
		rs_token_node = last_pipe->next;
		*head = last_pipe;
		(*head)->next = NULL;
	}
	*head = first_head;
	return (rs_token_node);
}

t_tree	*init_rs_node(t_token **head, t_token *last_pipe, bool is_first, t_tree *prev_node)
{
	t_tree	*rs_node;

	rs_node = (t_tree *)malloc(sizeof (t_tree));
	if (rs_node == NULL)
		return (NULL);
	rs_node->cmd_tokens = cmd_of_rs (head, last_pipe, is_first);
	rs_node->infile_tokens = NULL;
	rs_node->outfile_tokens = NULL;
	rs_node->prev = prev_node;
	rs_node->prev = NULL;
	rs_node->left = NULL;
	rs_node->right = NULL;
	return (rs_node);
}

t_tree	*rs_tree_node(t_token **head, t_token *last_pipe, bool is_first, t_tree *prev_node)
{
	t_token	*temp_head;
	t_tree	*node;

	temp_head = *head;
	node = init_rs_node (head, last_pipe, is_first, prev_node);
	if (!node)
		return (NULL);
	*head = last_pipe;
	(*head)->next = NULL;
	*head = temp_head;
	return (node);
}
