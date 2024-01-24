/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:45:31 by toshi             #+#    #+#             */
/*   Updated: 2024/01/17 22:04:10 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char *save_text_last(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	while(*ptr && !is_delim(*ptr))
		ptr++;
	return (--ptr);
}

char *save_space_last(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	while(*ptr && is_ifs(*ptr))
		ptr++;
	return (--ptr);
}

char *save_redir_last(char *begining)
{
	char *ptr;
	
	ptr = begining + sizeof(char);
	if (*begining == *ptr)
		return (ptr);
	else
		return (begining);
}

char *save_quote_last(char *begining)			//クォート内を抜き出す
{
	char *ptr;

	ptr = begining + sizeof(char);
	while(*ptr != '\0' && *ptr != *begining)
		ptr++;
	if (*ptr == '\0')
		return (NULL);
	return (ptr);
}

char *save_env_last(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	if (*ptr == '?' || *ptr == '$') 			//そのまま
		return (ptr);
	if (is_quote(*ptr))							//クォート内を抜き出す
		return (save_quote_last(ptr));
	if (*ptr == '\0' || is_delim(*ptr))			//そのまま
		return (begining);
	return (save_text_last(ptr));				//そのまま
}