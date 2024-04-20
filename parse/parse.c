/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:33:48 by username          #+#    #+#             */
/*   Updated: 2024/04/20 17:31:05 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	split_by_pipe(t_tree_node **tree, t_token **head, ssize_t count)
{
	t_tree_node	*tree_head;
	t_bool		is_root;
	t_token		*last_pipe;

	tree_head = *tree;
	is_root = TRUE;
	(*tree)->prev = NULL;
	while (count)
	{
		last_pipe = find_last_pipe (*head, count);
		(*tree)->right = rs_tree_node (head, last_pipe, is_root, *tree);
		(*tree)->init_data.cmd_tokens = \
		put_pipe_token (head, last_pipe, count);
		(*tree)->left = ls_tree_node (head, *tree);
		is_root = FALSE;
		*tree = (*tree)->left;
		count = count_pipe (*head);
	}
	*tree = tree_head;
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

t_token	*put_pipe_token(t_token **head, t_token *last_pipe, ssize_t count)
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

t_token	*find_last_pipe(t_token *head, ssize_t count)
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
