/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wrap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:20:50 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 17:31:29 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_tree_node	*parse_wrap(t_token *token_head)
{
	t_tree_node	*tree_head;
	ssize_t		count;

	tree_head = (t_tree_node *)calloc(sizeof(t_tree_node), 1);
	count = count_pipe(token_head);
	if (count == 0)
		tree_head->init_data.cmd_tokens = token_head;
	else
		split_by_pipe (&tree_head, &token_head, count);
	return (tree_head);
}

// void    parse(t_token **head)
// {
//         t_tree_node     node;
//         ssize_t         count;

//         node = (t_tree_node) malloc (sizeof (t_tree_node));
//         count = count_pipe (head);
//         if (count == 0)
//         {
//                 node->right = NULL;
//                 node->init_arg_data.cmd_tokens =head;
//                 *head = NULL;
//                 node->init_arg_data.infile_tokens = NULL;
//                 node->init_arg_data.outfile_tokens = NULL;
//                 node->left = NULL;
//                 node->prev = NULL;
//         }
//         else
//                 split_by_pipe (&tree, head, count);
// }