/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:45:31 by toshi             #+#    #+#             */
/*   Updated: 2024/01/26 10:11:31 by toshi            ###   ########.fr       */
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
	// ssize_t	i;

	// i = 1;
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
		return (-1);//error
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
