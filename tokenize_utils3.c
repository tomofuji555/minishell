/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:58:14 by toshi             #+#    #+#             */
/*   Updated: 2024/01/23 01:31:53 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
	// ssize_t	i;

	// i = 1;
	if (begining[0] == begining[1])
		return (2);
	else
		return (1);
}

ssize_t	count_quote_last(char *begining)			//クォート内を抜き出す
{
	ssize_t	i;

	i = 1;
	while(begining[i] && begining[0] != begining[i])
		i++;
	if (begining[i] == '\0')
		return (-1);//error
	return (i + 1);
}

ssize_t	count_dollar_last(char *begining)
{
	ssize_t	i;

	i = 1;
	if (begining[i] == '?' || begining[i] == '$') 			//そのまま
		return (1 + i);
	if (is_quote(begining[i]))							//クォート内を抜き出す
		return (1 + count_quote_last(&begining[i]));
	if ( begining[i] == '\0' || is_delim(begining[i]))			//そのまま
		return (1);
	return (1 + count_text_last(&begining[i]));				//そのまま
}