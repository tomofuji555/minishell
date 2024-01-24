/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:07:59 by toshi             #+#    #+#             */
/*   Updated: 2024/01/17 21:45:09 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//save_last~系は必ずptr->next!=NULLで止める
t_token *save_last_for_redir_tkns(t_token *tkn_ptr)
{
	tkn_ptr = tkn_ptr->next;
	while(tkn_ptr->kind == TKN_SPACE)
		tkn_ptr = tkn_ptr->next;
	while(tkn_ptr->next != NULL && is_valuable_token(tkn_ptr->next->kind))
		tkn_ptr = tkn_ptr->next;
	return (tkn_ptr);
}

static void	_push_to_redir_tkns_last(t_token **head, t_token *prev_first, t_token *last)
{
	if (*head == NULL)
		*head = prev_first->next;
	else
		tkn_find_last(*head)->next = prev_first->next;
	prev_first->next = last->next;
	last->next = NULL;
}

//init_data.cmd_tknsからリダイレクト対象のnodeをredir_tkns_headにpushする
t_token *push_redir_tkns(t_token *ptr, t_bool (*is_func)(enum e_token_kind))
{
	t_token *redir_tkns_head;
	t_token *last;

	// int i = 0;
	redir_tkns_head = NULL;
	while(ptr != NULL)
	{
		// printf("count=%d;\n", i++);
		// printf("val=%s;\n", ptr->val);
		if (ptr->next != NULL && is_func(ptr->next->kind))
		{
			last = save_last_for_redir_tkns(ptr->next);
			_push_to_redir_tkns_last(&redir_tkns_head, ptr, last);
		}
		ptr = ptr->next;
		// printf("next_add=%p;\n", ptr);
	}
	return (redir_tkns_head);
}