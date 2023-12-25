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

ssize_t	quort_token(t_token **head, char *line) 
{
	char	*start;
	int	TKN_KIND;
	int	flag;

	start = line;
	flag = 0;
	if (*start == '\'')
		TKN_KIND = TKN_S_QUOTE;
	else
		TKN_KIND = TKN_D_QUOTE;
	//line++;
	while (*line)
	{
		line++;
		if (*start == *line)
		{
			make_token_list (head, start + 1, line - start - 1, TKN_KIND);
			flag++;
			break;
		}	
	}
	//if (!flag)
		//error ();
	return (line - start + 1);
}
