/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wrap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:20:50 by toshi             #+#    #+#             */
/*   Updated: 2024/04/21 20:39:36 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"

static void	_del_space_afrer_redir(t_token **tkn_head)
{
	t_token *prev;
	t_token *ptr;

	prev = NULL;
	ptr = *tkn_head;
	while(ptr != NULL)
	{
		if (prev != NULL && is_redir_tkn(prev->kind) && ptr->kind == TKN_SPACE)
			remove_token(tkn_head, ptr, prev);
		prev = ptr;
		ptr = ptr->next;
	}
}

t_tree_node	*parse(t_token *token_head)
{
	t_tree_node	*tree_head;
	ssize_t		count;

	// syntax_check(&token_head);
	// if (token_head == NULL)
	// 	return (NULL);
	_del_space_afrer_redir(&token_head);
	tree_head = (t_tree_node *)ft_xcalloc(sizeof(t_tree_node), 1); //注意
	count = count_pipe(token_head);
	if (count == 0)
		tree_head->init_data.cmd_tokens = token_head;
	else
		split_by_pipe (&tree_head, &token_head, count);
	move_to_redir_tokens(tree_head);
	return (tree_head);
}
