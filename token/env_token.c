/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:49:04 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/26 17:58:20 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	quort_in_env(t_token **head, char *line)
{
	char	*start;
	int		flag;

	start = line;
	flag = 0;
	while (*line)
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
		quort_error ( );
	return (line - start + 1);
}

ssize_t	env_token(t_token **head, char *line)
{
	char	*start;

	start = line;
	line++;
	if (*line == '$' || *line == '?')
	{
		token_list (head, line, line - start, TKN_ENV);
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
		while (*line != '\0' && !is_metachar (*line))
			line++;
		token_list (head, start + 1, line - start - 1, TKN_ENV);
	}
	return (line - start);
}
