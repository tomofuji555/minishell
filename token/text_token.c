/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:51:05 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/27 23:53:46 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

ssize_t	text_token(t_token **head, char *line)
{
	char	*start;

	start = line;
	while (*line != '\0' && !is_metachar (*line) \
		&& *line != '\t' && *line != '\n')
		line++;
	token_list (head, start, line - start, TKN_TEXT);
	return (line - start);
}
