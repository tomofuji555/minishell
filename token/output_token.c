/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:50:37 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/25 19:50:39 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	output_token(t_token **head, char *line)
{
	char	*start;
	int		kind;

	start = line;
	while (*line != '\0' && *line == '>' && line - start <= 2)
		line++;
	if (*start == '>' && *(start + 1) == '>')
		kind = TKN_APPEND_FILE;
	else
		kind = TKN_OUT_FILE;
	token_list (head, start, line - start, kind);
	return (line - start);
}
