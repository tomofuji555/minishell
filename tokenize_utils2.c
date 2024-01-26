/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:39:39 by toshi             #+#    #+#             */
/*   Updated: 2024/01/26 10:13:31 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

enum e_token_kind	_save_redir_tkn_kind(char *begining)
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
enum e_token_kind	_save_env_or_text_kind(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	if (*ptr == '\0' || (*ptr != '?' && *ptr != '$' && is_delim(*ptr)))
		return (TKN_TEXT);
	return (TKN_ENV);
}

enum e_token_kind	save_tkn_kind(char *begining)
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
	else if(is_ifs(*begining))
		return (TKN_SPACE);
	else
		return (TKN_TEXT);
}

t_token	*find_last_tkn(t_token *head)
{
	t_token *ptr;

	ptr = head;
	while(ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void add_last_tkn(t_token **head, t_token *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_tkn(*head)->next = new;
}
