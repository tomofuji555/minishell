/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:05:26 by toshi             #+#    #+#             */
/*   Updated: 2024/04/25 21:17:39 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../utils/utils.h"

static size_t	count_arg_strs(t_token *ptr)
{
	size_t	i;

	i = 0;
	while (ptr != NULL)
	{
		if (is_valuable_token(ptr->kind))
		{
			i++;
			ptr = find_last_valuable_token(ptr);
		}
		ptr = ptr->next;
	}
	return (i);
}

//valuable_tknが一つもないtkn_listはNULLに変換される
char	**make_cmd_args(t_token *ptr)
{
	char	**cmd_args;
	size_t	count;
	size_t	i;
	t_token	*last;

	count = count_arg_strs(ptr);
	if (!count)
		return (NULL);
	cmd_args = (char **)ft_xmalloc(sizeof(char *) * (count + 1));
	i = 0;
	while (ptr != NULL)
	{
		if (is_valuable_token(ptr->kind))
		{
			last = find_last_valuable_token(ptr);
			cmd_args[i++] = substr_from_tkn(ptr, last);
			ptr = last;
		}
		ptr = ptr->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}
