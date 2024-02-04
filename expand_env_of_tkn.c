/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_of_tkn.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:10:12 by toshi             #+#    #+#             */
/*   Updated: 2024/02/02 20:44:11 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


static size_t _count_untill_last_and_set_kind(char *begining, enum e_token_kind *kind)
{
	ssize_t	i;

	if (is_ifs(*begining))
	{
		*kind = TKN_SPACE;
		return (count_untill_ifs_last(begining));
	}
	else
	{
		*kind = TKN_TEXT;	
		i = 1;
		while(begining[i] && !is_ifs(begining[i]))
			i++;
		return (i);
	}
}

static t_token *_tokenize_space_or_text(char *env_val)
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
		count = _count_untill_last_and_set_kind(env_val, &kind);
		new = make_new_tkn(env_val, count, kind);
		add_last_tkn(&head, new);
		env_val += count;
	}
	return (head);
}

void	expand_env_of_tkn(t_token **head, t_token *env_tkn, t_token *prev_of_env_tkn)
{
	t_token *expanded_head;
	
	expanded_head = _tokenize_space_or_text \
		(search_env_val(env_tkn->val, count_envname(env_tkn->val)));
	if (*head == env_tkn) //headをexpansionした場合  ここの条件文ないが問題
	{
		if (expanded_head == NULL) //env_tknのvalがなかった
			*head = env_tkn->next;
		else
		{
			*head = expanded_head;
			// tkn_print_lst(*head);
			// printf("------\n");
			// printf("lastnext=%p\n", env_tkn->next);
			find_last_tkn(expanded_head)->next = env_tkn->next;
		}
	}
	else //head以外をexpansionした場合
	{
		if (expanded_head == NULL) //env_tknのvalがなかった
			prev_of_env_tkn->next = env_tkn->next;
		else
		{
			prev_of_env_tkn->next = expanded_head;
			find_last_tkn(expanded_head)->next = env_tkn->next;
		}
	}
	free_tkn(env_tkn);
}
