/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:33:26 by toshi             #+#    #+#             */
/*   Updated: 2024/01/19 23:48:15 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char *save_last_chr(char *begining)
{
	if (*begining == '$')
		return (save_env_last(begining));
	else if (*begining == '\"' || *begining == '\'')
		return (save_quote_last(begining));
	else if (*begining == '>' || *begining == '<')
		return (save_redir_last(begining));
	else if (*begining == '|')
		return (begining);
	else if(is_ifs(*begining))
		return (save_space_last(begining));
	else
		return (save_text_last(begining));
}

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
t_token *tkn_make_new(char *begining, char *last)
{
	t_token *node = (t_token *)malloc(sizeof(t_token));
	if(is_quote(*last))
		node->val = tkn_substr_into_quote(begining, last);
	else
		node->val = tkn_substr(begining, last);
	node->kind = tkn_save_kind(begining);
	node->next = NULL;
	return (node);
}

t_token *tokenize(char *line_ptr)
{
	char		*last;
	// ssize_t		count;
	t_token 	*head;
	t_token 	*new;

	head = NULL;
	while(*line_ptr)
	{
		// count =  count_last(line_ptr);
		last = save_last_chr(line_ptr);
		// print_to_last(line_ptr, &line_ptr[count - 1]);
		if (last == NULL)
		{
			tkn_free_lst(head);
			return (NULL);
		}
		new = tkn_make_new(line_ptr, last);
		tkn_add_last(&head, new);
		// line_ptr += sizeof(char) * (count);
		line_ptr = ++last;
	}
	return (head);
}

// ft_putendl_fd("Once you have entered the quotation, \
// 				please close it properly >:( ", STDERR_FILENO);