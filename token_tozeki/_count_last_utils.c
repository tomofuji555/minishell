/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _count_last_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:03:38 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 19:48:24 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "../utils/utils.h"

ssize_t	count_text_last(char *first)
{
	ssize_t	i;

	i = 1;
	while (first[i] && !is_delim(first[i]))
		i++;
	return (i);
}

ssize_t	count_ifs_last(char *first)
{
	ssize_t	i;

	i = 1;
	while (first[i] && is_ifs(first[i]))
		i++;
	return (i);
}

ssize_t	count_redir_last(char *first)
{
	if (first[0] == first[1])
		return (2);
	else
		return (1);
}

//閉じクォートが来ないで文末に来た場合、-1を返す
ssize_t	count_quote_last(char *first)
{
	ssize_t	i;

	i = 1;
	while (first[i] && first[0] != first[i])
		i++;
	if (first[i] == '\0')
		return (-1);
	return (i + 1);
}

//$"---"のパターンのみクォート内の文字数を数える
ssize_t	count_dollar_last(char *first)
{
	char	*next;
	size_t	count;

	next = first + sizeof(char);
	if (*next == '?' || *next == '$')
		return (2);
	if (is_quote(*next))
	{
		count = count_quote_last(next);
		if (count == -1)
			return (-1);
		return (1 + count);
	}
	if (*next == '\0' || is_delim(*next))
		return (1);
	return (1 + count_text_last(next));
}
