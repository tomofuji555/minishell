/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:33:26 by toshi             #+#    #+#             */
/*   Updated: 2024/01/26 10:14:42 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

ssize_t _count_untill_last(char *begining)
{
	if (*begining == '$')
		return (count_untill_dollar_last(begining));
	else if (*begining == '\"' || *begining == '\'')
		return (count_untill_quote_last(begining));
	else if (*begining == '>' || *begining == '<')
		return (count_untill_redir_last(begining));
	else if (*begining == '|')
		return (1);
	else if(is_ifs(*begining))
		return (count_untill_ifs_last(begining));
	else
		return (count_untill_text_last(begining));
}

//lenはクォーテーション内の文字数+1文字分
static char *_substr_into_quote(char *begining, size_t count)
{
	if (*begining == '$')
	{
		begining++;
		count--;
	}
	// if (*begining == *(begining + 1))
	// 	return (ft_xstrdup(""));
	return (ft_xsubstr(begining, 1, count - 2));
}

// is_quote(*last)で判断したいのは、クォートトークンか{$""/$''}の形かどうか
t_token *make_new_tkn(char *begining, ssize_t count, enum e_token_kind kind)
{
	t_token	*node;
	node = (t_token *)malloc(sizeof(t_token));
	if (is_quote(begining[count - 1]))
		node->val = _substr_into_quote(begining, (size_t)count);
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
		count = _count_untill_last(line_ptr);
		if (count == -1)
		{
			tkn_free_lst(head);
			return (NULL);
		}
		new = make_new_tkn(line_ptr, count, save_tkn_kind(line_ptr));
		add_last_tkn(&head, new);
		line_ptr += count;
	}
	return (head);
}

// ft_putendl_fd("Once you have entered the quotation, \
// 				please close it properly >:( ", STDERR_FILENO);