/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_tkn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:15:59 by toshi             #+#    #+#             */
/*   Updated: 2024/04/18 22:47:55 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../utils/utils.h"
#include "../token_tozeki/tokenize.h"

static void _set_kind_and_count(char *begining, enum e_token_kind *kind, ssize_t *count)
{
	ssize_t	i;

	if (is_ifs(*begining))
	{
		*kind = TKN_SPACE;
		*count = count_ifs_last(begining);
	}
	else
	{
		*kind = TKN_TEXT;
		i = 1;
		while(begining[i] && !is_ifs(begining[i]))
			i++;
		*count = i;
	}
}

static t_token *tokenize_space_or_text(char *env_val)
{
	t_token 			*head;
	t_token				*new;
	ssize_t				count;
	enum e_token_kind	kind;

	if (env_val == NULL)
		return (NULL);
	head = NULL;
	while(*env_val)
	{
		_set_kind_and_count(env_val, &kind, &count);
		new = make_new_tkn(env_val, count, kind);
		add_tkn_last(&head, new);
		env_val += count;
	}
	return (head);
}

t_token	*expand_env_tkn(t_token **dest_head, t_token *env_tkn, t_token *prev, t_manager *manager)
{
	t_token *next_ptr;
	t_token *expnad_list;

	next_ptr = env_tkn->next;
	expnad_list = tokenize_space_or_text(ms_getenv(env_tkn->val + sizeof(char), manager));
	if (expnad_list == NULL)
	{
		if (prev == NULL)
			*dest_head = next_ptr;
		else
			prev->next = next_ptr;
	}
	else
	{
		if (prev == NULL)
			*dest_head = expnad_list;
		else
			prev->next = expnad_list;
		find_last_tkn(expnad_list)->next = next_ptr;
	}
	free_tkn(env_tkn);
	return (next_ptr);
}