/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:40:26 by toshi             #+#    #+#             */
/*   Updated: 2024/02/02 21:35:40 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

size_t _count_strs(t_token *tkn_ptr)
{
	size_t i;

	i = 1;
	while (tkn_ptr != NULL)
	{
		if (tkn_ptr->kind != TKN_SPACE) //is_valuable_tknでもアリ
		{
			i++;
			tkn_ptr = find_last_valuable_tkn(tkn_ptr);
		}
		tkn_ptr = tkn_ptr->next;
	}
	return (i);
}

char **_insert_strs_from_tkns(t_token *tkn_ptr, char **cmd_args)
{
	size_t i;
	t_token *last;

	i = 0;
	while(tkn_ptr != NULL)
	{
		if (tkn_ptr->kind != TKN_SPACE) //is_valuable_tknでもアリ
		{
			last = find_last_valuable_tkn(tkn_ptr);
			cmd_args[i++] = substr_from_tkn(tkn_ptr, last);
			tkn_ptr = last;
		}
		tkn_ptr = tkn_ptr->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

char **make_cmd_args(t_token *tkn_head)
{
	char **cmd_args;

	cmd_args = (char **)ft_xmalloc(sizeof(char *) * _count_strs(tkn_head));
	return (_insert_strs_from_tkns(tkn_head, cmd_args));
}