/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wrap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:20:50 by toshi             #+#    #+#             */
/*   Updated: 2024/05/03 12:13:15 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../utils/utils.h"

// token_listの最後がリダイレクト->スペースになることは、
// syntax_errorではじいているため、ない
static void	remove_space_afrer_redir(t_token **tkn_head)
{
	t_token	*ptr;
	t_token	*target;
	t_token	*target_prev;

	target = *tkn_head;
	ptr = target->next;
	while (ptr != NULL)
	{
		target_prev = search_prev_token(*tkn_head, target);
		if (target_prev && is_redir_tkn(target_prev->kind) \
			&& target->kind == TKN_SPACE)
			remove_token(tkn_head, target, target_prev);
		target = ptr;
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
