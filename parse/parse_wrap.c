/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wrap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:20:50 by toshi             #+#    #+#             */
/*   Updated: 2024/04/12 23:39:38 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_tree_node	*parse_wrap(t_token *token_head)
{
	t_tree_node *head;

	head = NULL;
	split_by_pipe(&head, &token_head, count_pipe(token_head));
	return (head);
}