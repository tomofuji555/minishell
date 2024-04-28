/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:49:04 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/04/26 20:38:43 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

ssize_t	quort_in_env(t_token **head, char *line)
{
	char	*start;
	int		flag;

	start = line;
	flag = 0;
	while (*line != '\0')
	{
		line++;
		if (*start == *line)
		{
			token_list (head, start + 1, line - start - 1, TKN_TEXT);
			flag++;
			break ;
		}
	}
	if (!flag)
		return (quort_error (*start));
	return (line - start + 2);
}

ssize_t	env_token(t_token **head, char *line)
{
	char	*start;

	start = line;
	line++;
	if (*line == '$' || *line == '?')
	{
		token_list (head, start, line - start + 1, TKN_ENV);
		return (line - start + 1);
	}
	else if (*line == '\'' || *line == '\"')
		return (quort_in_env (head, line));
	else if (*line == ' ' || *line == '>' || *line == '<' || *line == '|')
	{
		token_list (head, start, line - start, TKN_TEXT);
		return (line - start);
	}
	else
	{
		while (*line != '\0' && !is_metachar (*line) && *line != ':')
			line++;
		token_list (head, start, line - start, TKN_ENV);
	}
	return (line - start);
}
