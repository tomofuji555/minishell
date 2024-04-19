/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:33:26 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 01:25:49 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

static ssize_t _count_last(char *begining)
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

static enum e_token_kind	_save_redir_tkn_kind(char *begining)
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
static enum e_token_kind	_save_env_or_text_kind(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	if (*ptr == '\0' || (*ptr != '?' && *ptr != '$' && is_delim(*ptr)))
		return (TKN_TEXT);
	return (TKN_ENV);
}

static enum e_token_kind	_save_tkn_kind(char *begining)
{
	if (*begining == '$')
		return (_save_env_or_text_kind(begining));
	else if (*begining == '\'')
		return (TKN_S_QUOTE);
	else if (*begining == '\"')
		return (TKN_D_QUOTE);
	else if (*begining == '<' || *begining == '>')
		return (_save_redir_tkn_kind(begining));
	else if (*begining == '|')
		return (TKN_PIPE);
	else if (is_ifs(*begining))
		return (TKN_SPACE);
	else
		return (TKN_TEXT);
}

t_token *tokenize(char *line_ptr)
{
	t_token		*head;
	t_token		*new;
	ssize_t		count;

	head = NULL;
	while (*line_ptr)
	{
		count = _count_last(line_ptr);
		if (count == -1)
		{
			free_token_list(head);
			ft_putendl_fd("please close the quotation", STDERR_FILENO);
			return (NULL);
		}
		new = make_new_tkn(line_ptr, count, _save_tkn_kind(line_ptr));
		add_token_last(&head, new);
		line_ptr += count;
	}
	return (head);
}
