/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:40:15 by username          #+#    #+#             */
/*   Updated: 2024/04/22 22:28:07 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

t_tree_node	*init_ls_node(t_token **head, t_token *last_pipe, \
t_tree_node *prev_node)
{
	t_tree_node	*ls_node;

	ls_node = (t_tree_node *)ft_xmalloc(sizeof(t_tree_node));
	if (ls_node == NULL)
		return (NULL);
	ls_node->init_data.cmd_tokens = NULL;
	if (last_pipe == NULL)
	{
		ls_node->init_data.cmd_tokens = *head;
		*head = NULL;
	}
	ls_node->init_data.outfile_tokens = NULL;
	ls_node->init_data.infile_tokens = NULL;
	ls_node->prev = prev_node;
	ls_node->left = NULL;
	ls_node->right = NULL;
	return (ls_node);
}

t_tree_node	*ls_tree_node(t_token **head, t_tree_node *prev_node)
{
	t_tree_node	*ls_node;
	t_token		*last_pipe;
	ssize_t		count;

	count = count_pipe (*head);
	last_pipe = find_last_pipe (*head, count);
	ls_node = init_ls_node (head, last_pipe, prev_node);
	return (ls_node);
}
