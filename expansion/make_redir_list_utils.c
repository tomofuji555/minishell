/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:04:22 by toshi             #+#    #+#             */
/*   Updated: 2024/04/30 19:27:08 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../utils/utils.h"

static t_bool	contains_quote(t_token *first)
{
	t_token	*ptr;

	ptr = first->next;
	while (ptr && !is_redir_tkn(ptr->kind))
	{
		if (ptr->kind == TKN_S_QUOTE || ptr->kind == TKN_D_QUOTE)
			return (TRUE);
		ptr = ptr->next;
	}
	return (FALSE);
}

enum e_redir_kind	convert_redir_kind(t_token *first)
{
	if (first->kind == TKN_IN_FILE)
		return (REDIR_IN_FILE);
	else if (first->kind == TKN_HEREDOC)
	{
		if (contains_quote(first))
			return (REDIR_HEREDOC_NO_EXPAND);
		else
			return (REDIR_HEREDOC);
	}
	else if (first->kind == TKN_OUT_FILE)
		return (REDIR_OUT_FILE);
	else
		return (REDIR_APPEND_FILE);
}

static t_redir	*find_last_redir(t_redir *ptr)
{
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	add_redir_last(t_redir **head, t_redir *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_redir(*head)->next = new;
}
