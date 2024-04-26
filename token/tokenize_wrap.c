/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_wrap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:11:11 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 21:46:07 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "../utils/utils.h"

t_token	*tokenize(char *line)
{
	t_token	*tkn_list;

	tkn_list = NULL;
	if (split_to_token(&tkn_list, line) == -1)
	{
		free_token_list(tkn_list);
		return (NULL);
	}
	if (!validate_syntax(tkn_list))
	{
		free_token_list(tkn_list);
		return (NULL);
	}
	return (tkn_list);
}
