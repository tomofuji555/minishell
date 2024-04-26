/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:33:26 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 19:35:13 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

static ssize_t	count_last(char *first)
{
	if (*first == '$')
		return (count_dollar_last(first));
	else if (*first == '\"' || *first == '\'')
		return (count_quote_last(first));
	else if (*first == '>' || *first == '<')
		return (count_redir_last(first));
	else if (*first == '|')
		return (1);
	else if (is_ifs(*first))
		return (count_ifs_last(first));
	else
		return (count_text_last(first));
}

static enum e_token_kind	save_redir_tkn_kind(char *first)
{
	char	*next;

	next = first + sizeof(char);
	if (*first == '<')
	{
		if (*first == *next)
			return (TKN_HEREDOC);
		else
			return (TKN_IN_FILE);
	}
	else
	{
		if (*first == *next)
			return (TKN_APPEND_FILE);
		else
			return (TKN_OUT_FILE);
	}
}

//$の次がヌル終端か、?・$以外の区切り文字ならTKN_TEXT
static enum e_token_kind	save_env_or_text_kind(char *first)
{
	char	*next;

	next = first + sizeof(char);
	if (*next == '\0' || (*next != '?' && *next != '$' && is_delim(*next)))
		return (TKN_TEXT);
	return (TKN_ENV);
}

static enum e_token_kind	save_tkn_kind(char *first)
{
	if (*first == '$')
		return (save_env_or_text_kind(first));
	else if (*first == '\'')
		return (TKN_S_QUOTE);
	else if (*first == '\"')
		return (TKN_D_QUOTE);
	else if (*first == '<' || *first == '>')
		return (save_redir_tkn_kind(first));
	else if (*first == '|')
		return (TKN_PIPE);
	else if (is_ifs(*first))
		return (TKN_SPACE);
	else
		return (TKN_TEXT);
}

t_token	*tokenize(char *ptr)
{
	t_token		*head;
	t_token		*new;
	ssize_t		count;

	head = NULL;
	while (*ptr)
	{
		count = count_last(ptr);
		if (count == -1)
		{
			free_token_list(head);
			ft_putendl_fd("please close the quotation", STDERR_FILENO);
			return (NULL);
		}
		new = make_new_token(ptr, count, save_tkn_kind(ptr));
		add_token_last(&head, new);
		ptr += count;
	}
	return (head);
}
