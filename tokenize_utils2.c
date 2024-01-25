/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:39:39 by toshi             #+#    #+#             */
/*   Updated: 2024/01/25 23:22:40 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

enum e_token_kind	save_redir_tkn_kind(char *begining)
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
enum e_token_kind	save_env_or_text_kind(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	if (*ptr == '\0' || (*ptr != '?' && *ptr != '$' && is_delim(*ptr)))
		return (TKN_TEXT);
	return (TKN_ENV);
}

//lenはクォーテーション内の文字数+1文字分
char *tkn_substr_into_quote(char *begining, ssize_t count)
{
	if (*begining == '$')
		begining++;
	if (*begining == *(begining + 1))
		count = 0;
	return (ft_xsubstr(begining, 1, (size_t)len - 1));
}
