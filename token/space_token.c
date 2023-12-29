/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:50:58 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/25 19:51:00 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	space_token(t_token **head, char *line)
{
	char	*start;

	start = line;
	while (*line != '\0' && (*line == ' ' || *line == '\t' || *line == '\n'))
		line++;
	token_list (head, start, line - start, TKN_SPACE);
	return (line - start);
}
