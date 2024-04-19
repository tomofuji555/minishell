/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _count_last_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:03:38 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 01:20:34 by toshi            ###   ########.fr       */
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
	size_t count;

	next = begining + sizeof(char);
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
