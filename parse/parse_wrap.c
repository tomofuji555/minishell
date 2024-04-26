/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wrap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:20:50 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 19:28:25 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"

static void	remove_space_afrer_redir(t_token **tkn_head)
{
	t_token	*prev;
	t_token	*ptr;

	prev = NULL;
	ptr = *tkn_head;
	while (ptr != NULL)
	{
		if (prev != NULL && is_redir_tkn(prev->kind) && ptr->kind == TKN_SPACE)
			remove_token(tkn_head, ptr, prev);
		prev = ptr;
		ptr = ptr->next;
	}
}

t_tree_node	*parse(t_token *tkn_head)
{
	t_tree_node	*root;
	ssize_t		count;

	remove_space_afrer_redir(&tkn_head);
	root = (t_tree_node *)ft_xcalloc(sizeof(t_tree_node), 1);
	count = count_pipe(tkn_head);
	if (count == 0)
		root->init_data.cmd_tokens = tkn_head;
	else
		split_by_pipe (&root, &tkn_head, count);
	move_to_redir_tokens(root);
	return (root);
}
