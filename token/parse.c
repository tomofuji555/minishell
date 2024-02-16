#include "minishell.h"

void	split_by_pipe(t_tree_node **tree, t_token **head, ssize_t count)
{
	t_tree_node	*prev_tree;
	t_bool		is_root;
	t_token		*last_pipe;

	is_root = TRUE;
	prev_tree = NULL;
	while (count)
	{
		last_pipe = find_last_pipe (*head, count);
		(*tree)->right = rs_tree_node (head, last_pipe, is_root, prev_tree);
		(*tree)->init_arg_data->cmd_tokens = cmd_token (head, last_pipe, count);//last_pipeを入れる関数;
		(*tree)->left = ls_tree_node (head, prev_tree);
		(*tree)->prev = prev_node (prev_tree);
		//if (!check_tree (*tree))
			//return ;
		is_root = FALSE;
		prev_tree = *tree;
		*tree = (*tree)->left;
		count = count_pipe (*head);
	}
}

ssize_t	count_pipe(t_token *head)
{
	ssize_t	count;

	count = 0;
	while (head != NULL)
	{
		if (head->kind == TKN_PIPE)
			count++;
		head = head->next;
	}
	return (count);
}

t_token	*find_prev_last_pipe(t_token *head, ssize_t count)
{
	t_token	*current_head;
	ssize_t	pipe_count;

	current_head = head;
	pipe_count = 0;
	while (current_head->next != NULL)
	{
		if (current_head->next->kind == TKN_PIPE)
			pipe_count++;
		if (pipe_count == count)
			return (current_head);
		current_head = current_head->next;
	}
	return (head);
}

t_token	*cmd_token(t_token **head, t_token *last_pipe, ssize_t count)
{
	t_token	*temp_head;
	t_token	*prev_last_pipe;

	temp_head = *head;
	prev_last_pipe = find_prev_last_pipe (*head, count);
	*head = prev_last_pipe;
	(*head)->next = last_pipe->next;
	(*head) = temp_head;
	return (last_pipe);
}

t_token	*find_last_pipe(t_token *head, ssize_t count) //problem
{
	t_token	*current_head;
	ssize_t	pipe_count;

	current_head = head;
	pipe_count = 0;
	while (current_head != NULL)
	{
		if (current_head->kind == TKN_PIPE)
		{
			pipe_count++;
			if (count == pipe_count)
				break ;
		}
		current_head = current_head->next;
	}
	if (pipe_count == 0)
		current_head = NULL;
	return (current_head);
}
