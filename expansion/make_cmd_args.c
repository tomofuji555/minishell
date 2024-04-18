/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:05:26 by toshi             #+#    #+#             */
/*   Updated: 2024/04/18 22:49:50 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../utils/utils.h"

static size_t count_arg_strs(t_token *tkn_ptr)
{
	size_t i;

	i = 0;
	while (tkn_ptr != NULL)
	{
		if (is_valuable_tkn(tkn_ptr->kind))
		{
			i++;
			tkn_ptr = find_last_valuable_tkn(tkn_ptr);
		}
		tkn_ptr = tkn_ptr->next;
	}
	return (i);
}

//valuable_tknが一つもないtkn_listはNULLに変換される
char **make_cmd_args(t_token *tkn_ptr)
{
	char	**cmd_args;
	size_t	count;
	size_t	i;
	t_token	*last;

	count = count_arg_strs(tkn_ptr);
	if (!count)
		return (NULL);
	cmd_args = (char **)ft_xmalloc(sizeof(char *) * (count + 1));
	i = 0;
	while(tkn_ptr != NULL)
	{
		if (is_valuable_tkn(tkn_ptr->kind))
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