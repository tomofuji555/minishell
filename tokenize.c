/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:33:26 by toshi             #+#    #+#             */
/*   Updated: 2024/02/08 09:54:18 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

ssize_t	count_untill_text_last(char *begining)
{
	ssize_t	i;

	i = 1;
	while(begining[i] && !is_delim(begining[i]))
		i++;
	return (i);
}

ssize_t	count_untill_ifs_last(char *begining)
{
	ssize_t	i;

	i = 1;
	while(begining[i] && is_ifs(begining[i]))
		i++;
	return (i);
}

ssize_t	count_untill_redir_last(char *begining)
{
	if (begining[0] == begining[1])
		return (2);
	else
		return (1);
}

ssize_t	count_untill_quote_last(char *begining)			//クォート内を抜き出す
{
	ssize_t	i;

	i = 1;
	while(begining[i] && begining[0] != begining[i])
		i++;
	if (begining[i] == '\0')
		return (-1);									//error
	return (i + 1);
}

ssize_t	count_untill_dollar_last(char *begining)
{
	char *next;

	next = begining + sizeof(char);
	if (*next == '?' || *next == '$') 			//そのまま
		return (2);
	if (is_quote(*next))							//クォート内を抜き出す
		return (1 + count_untill_quote_last(next));
	if (*next == '\0' || is_delim(*next))			//そのまま
		return (1);
	return (1 + count_untill_text_last(next));				//そのまま
}

static ssize_t count_untill_last(char *begining)
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
		count = count_untill_last(line_ptr);
		if (count == -1)
		{
			free_tkn_lst(head);
			ft_putendl_fd("Once you have entered the quotation, \
						please close it properly >:( ", STDERR_FILENO);
			return (NULL);
		}
		new = make_new_tkn(line_ptr, count, save_tkn_kind(line_ptr));
		add_tkn_last(&head, new);
		line_ptr += count;
	}
	return (head);
}
