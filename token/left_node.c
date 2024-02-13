#include "minishell.h"

t_token	*cmd_of_ls(t_token **head, t_token **last_pipe)
{
	t_token	*temp_head;
	t_token	*temp_last_pipe;

	temp_last_pipe = *last_pipe;
	if (*last_pipe == NULL)
	{
		temp_head = *head;
		*head = NULL;
		return (temp_head);
	}
	(*last_pipe)->next = NULL;
	(*last_pipe) = temp_last_pipe;
	return (*last_pipe);
}

t_tree	*init_ls_node(t_token **head, t_token *last_pipe, t_tree *prev_node)
{
	t_tree	*ls_node;

	ls_node = (t_tree *)malloc(sizeof(t_tree));
	if (ls_node == NULL)
		return (NULL);
	ls_node->cmd_tokens = NULL;
	if (last_pipe == NULL)
	{
		ls_node->cmd_tokens = *head;
		*head = NULL;
	}
	ls_node->outfile_tokens = NULL;
	ls_node->infile_tokens = NULL;
	ls_node->prev = prev_node;
	ls_node->left = NULL;
	ls_node->right = NULL;
	return (ls_node);
}

t_tree	*ls_tree_node(t_token **head, t_tree *prev_node)
{
	t_tree	*ls_node;
	t_token	*last_pipe;
	ssize_t	count;

	count = count_pipe (*head);
	last_pipe = find_last_pipe (*head, count);
	ls_node = init_ls_node (head, last_pipe, prev_node);
	return (ls_node);
}
