/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:10:12 by toshi             #+#    #+#             */
/*   Updated: 2024/01/18 15:42:04 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static size_t _count_offset_last(char *ptr)
{
	size_t	i;

	i = 0;
	if (is_ifs(ptr[i]))
	{
		while(ptr[i] && is_ifs(ptr[i]))
			i++;
	}
	else
	{
		while(ptr[i] && !is_ifs(ptr[i]))
			i++;
	}
	return (i);
}

static t_token *_tokenize_space_or_text(char *env_val)
{
	t_token 			*tkn_head;
	t_token				*new_tkn;
	enum e_token_kind	kind;
	// size_t				offset_last;
	char 	*last;

	tkn_head = NULL;
	while(*env_val)
	{
		if (is_ifs(*env_val))
			kind = TKN_SPACE;
		else
			kind = TKN_TEXT;
		last = save_last_chr(env_val);
		new_tkn = tkn_make_new(env_val, last);
		tkn_add_last(&tkn_head, new_tkn);
		// env_val += sizeof(char) * offset_last;
		env_val = ++last;
	}
	
	return (tkn_head);
}

t_token *expand_env(t_token *env_tkn)
{
	char *env_val;
	t_token *lst_head;
	
	env_val = search_env_val(env_tkn->val, count_envname(env_tkn->val));
	if (env_val == NULL)
	{
		// prev_env_tkn->next = env_tkn->next;
		// tkn_free(env_tkn);
		// return ;
		return (NULL);
	}
	lst_head = _tokenize_space_or_text(env_val);
	return (lst_head);
}
