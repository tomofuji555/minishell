/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:50:11 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/25 19:50:13 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	input_token(t_token **head, char *line)
{
	char	*start;
	int	TKN_KIND;

	start = line;
	while (*line != '\0' && *line == '<' && line - start <= 2)
		line++;
	if (*start == '<' && *(start + 1) == '<')
		TKN_KIND = TKN_HERE_DOC;
	else
		TKN_KIND = TKN_IN_FILE;
	make_token_list (head, start, line - start, TKN_KIND);
	return (line - start);
}
