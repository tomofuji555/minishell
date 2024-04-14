/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:33:26 by toshi             #+#    #+#             */
/*   Updated: 2024/04/14 13:00:06 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "../utils/utils.h"

ssize_t	count_text_last(char *begining)
{
	ssize_t	i;

	i = 1;
	while(begining[i] && !is_delim(begining[i]))
		i++;
	return (i);
}

ssize_t	count_ifs_last(char *begining)
{
	ssize_t	i;

	i = 1;
	while(begining[i] && is_ifs(begining[i]))
		i++;
	return (i);
}

ssize_t	count_redir_last(char *begining)
{
	if (begining[0] == begining[1])
		return (2);
	else
		return (1);
}

//閉じクォートが来ないで文末に来た場合、-1を返す
ssize_t	count_quote_last(char *begining)
{
	ssize_t	i;

	i = 1;
	while(begining[i] && begining[0] != begining[i])
		i++;
	if (begining[i] == '\0')
		return (-1);
	return (i + 1);
}

//$"---"のパターンのみクォート内の文字数を数える
ssize_t	count_dollar_last(char *begining)
{
	char *next;

	next = begining + sizeof(char);
	if (*next == '?' || *next == '$')
		return (2);
	if (is_quote(*next))
		return (1 + count_quote_last(next));
	if (*next == '\0' || is_delim(*next))
		return (1);
	return (1 + count_text_last(next));
}

static ssize_t count_last(char *begining)
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
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

static enum e_token_kind	save_redir_tkn_kind(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	if (*begining == '<')
	{
		if (*begining == *ptr)
			return (TKN_HEREDOC);
		else
			return (TKN_IN_FILE);
	}
	else
	{
		if (*begining == *ptr)
			return (TKN_APPEND_FILE);
		else
			return (TKN_OUT_FILE);
	}
}

//$の次がヌル終端か、?・$以外の区切り文字ならTKN_TEXT
static enum e_token_kind	save_env_or_text_kind(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	if (*ptr == '\0' || (*ptr != '?' && *ptr != '$' && is_delim(*ptr)))
		return (TKN_TEXT);
	return (TKN_ENV);
}

static enum e_token_kind	save_tkn_kind(char *begining)
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
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

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
		count = count_last(line_ptr);
		if (count == -1)
		{
			free_tkn_list(head);
			ft_putendl_fd("please close the quotation", STDERR_FILENO);
			return (NULL);
		}
		new = make_new_tkn(line_ptr, count, save_tkn_kind(line_ptr));
		add_tkn_last(&head, new);
		line_ptr += count;
	}
	return (head);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */
