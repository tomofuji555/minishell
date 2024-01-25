/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:33:26 by toshi             #+#    #+#             */
/*   Updated: 2024/01/25 23:23:18 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

ssize_t count_last(char *begining)
{
	if (*begining == '$')
		return (count_dollar_last(begining));
	else if (*begining == '\"' || *begining == '\'')
		return (count_quote_last(begining));
	else if (*begining == '>' || *begining == '<')
		return (count_redir_last(begining));
	else if (*begining == '|')
		return (1);
	else if(is_ifs(*begining))
		return (count_ifs_last(begining));
	else
		return (count_text_last(begining));
}

enum e_token_kind	tkn_save_kind(char *begining)
{
	if (*begining == '$')
		return (save_env_or_text_kind(begining));
	else if (*begining == '\'')
		return (TKN_S_QUOTE);
	else if (*begining == '\"')
		return (TKN_D_QUOTE);
	else if (*begining == '<' || *begining == '>')
		return (save_redir_tkn_kind(begining));
	else if (*begining == '|')
		return (TKN_PIPE);
	else if(is_ifs(*begining))
		return (TKN_SPACE);
	else
		return (TKN_TEXT);
}

// is_quote(*last)で判断したいのは、クォートトークンか{$""/$''}の形かどうか
t_token *tkn_make_new(char *begining, ssize_t count, enum e_token_kind kind)
{
	t_token	*node;
	node = (t_token *)malloc(sizeof(t_token));
	if (is_quote(begining[count - 1]))
		node->val = substr_into_quote(begining, count);
	else
		node->val = ft_xsubstr(begining, 0, (size_t)count);
	node->kind = kind;
	node->next = NULL;
	return (node);
}

t_token *tokenize(char *line_ptr)
{
	t_token		*head;
	t_token		*new;
	ssize_t		count;

	head = NULL;
	while (*line_ptr)
	{
		count = count_last(line_ptr);
		if (count == -1)
		{
			tkn_free_lst(head);
			return (NULL);
		}
		new = tkn_make_new(line_ptr, count, tkn_save_kind(line_ptr));
		tkn_add_last(&head, new);
		line_ptr += count;
	}
	return (head);
}

// ft_putendl_fd("Once you have entered the quotation, \
// 				please close it properly >:( ", STDERR_FILENO);