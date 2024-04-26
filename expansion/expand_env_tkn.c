/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_tkn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:15:59 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 21:11:47 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../utils/utils.h"
#include "../token/tokenize.h"

static void	set_kind_and_count(char *first, \
		enum e_token_kind *kind, ssize_t *count)
{
	ssize_t	i;

	if (is_ifs(*first))
	{
		*kind = TKN_SPACE;
		*count = count_ifs_last(first);
		return ;
	}
	*kind = TKN_TEXT;
	i = 1;
	while (first[i] && !is_ifs(first[i]))
		i++;
	*count = i;
	return ;
}

static t_token	*tokenize_space_or_text(char *env_val)
{
	t_token				*head;
	t_token				*new;
	ssize_t				count;
	enum e_token_kind	kind;

	if (env_val == NULL)
		return (NULL);
	head = NULL;
	while (*env_val)
	{
		set_kind_and_count(env_val, &kind, &count);
		new = make_new_token(env_val, count, kind);
		add_token_last(&head, new);
		env_val += count;
	}
	return (head);
}

t_token	*expand_env_token(t_token **head, t_token *env_tkn, \
	t_token *prev_env, t_manager *manager)
{
	t_token	*next_ptr;
	t_token	*expnad_list;

	next_ptr = env_tkn->next;
	expnad_list = tokenize_space_or_text(ms_getenv(env_tkn->val + \
					sizeof(char), manager));
	if (expnad_list == NULL)
	{
		if (prev_env == NULL)
			*head = next_ptr;
		else
			prev_env->next = next_ptr;
	}
	else
	{
		if (prev_env == NULL)
			*head = expnad_list;
		else
			prev_env->next = expnad_list;
		find_last_token(expnad_list)->next = next_ptr;
	}
	free_token(env_tkn);
	return (next_ptr);
}
