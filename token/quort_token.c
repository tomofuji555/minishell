/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quort_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:50:51 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/04/26 21:42:22 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "../libft/libft.h"

ssize_t	quort_error(char c)
{
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	ft_putstr_fd(": syntax error near unexpected token \'", STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
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
		return (quort_error (*start));
	return (line - start + 1);
}
