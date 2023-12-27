/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:51:05 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/25 19:51:07 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	text_token(t_token **head, char *line)
{
	ssize_t	rt;
	char	*start;

	rt = 0;
	start = line;
	while (*line != '\0' && !is_metachar (*line) \
		&& *line != '\t' && *line != '\n')
	{
		rt++;
		line++;
	}
	token_list (head, start, rt, TKN_TEXT);
	return (rt);
}
