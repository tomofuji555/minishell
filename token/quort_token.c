/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quort_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:50:51 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/25 19:50:53 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	quort_error(void)
{
	printf ( "Argument is not surrounded by quort\n");
	return (-1);
}

ssize_t	quort_token(t_token **head, char *line)
{
	char	*start;
	int		kind;
	int		flag;

	start = line;
	flag = 0;
	if (*start == '\'')
		kind = TKN_S_QUOTE;
	else
		kind = TKN_D_QUOTE;
	while (*line)
	{
		line++;
		if (*start == *line)
		{
			token_list (head, start + 1, line - start - 1, kind);
			flag++;
			break ;
		}
	}
	if (!flag)
		return (quort_error ( ));
	return (line - start + 1);
}
