/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bool_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:09 by toshi             #+#    #+#             */
/*   Updated: 2024/01/21 20:04:19 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_bool is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_bool is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

t_bool is_delim(char c)
{
	return (is_ifs(c) || is_quote(c) || c == '<' || c == '>' \
		|| c == '$' || c == '|' || c == '\0');
}

t_bool is_valuable_token(enum e_token_kind kind)
{
	return (kind == TKN_TEXT || kind == TKN_S_QUOTE \
		|| kind == TKN_D_QUOTE || kind == TKN_ENV);
}

t_bool	is_in_redir_tkn(enum e_token_kind kind)
{
	return (kind == TKN_IN_FILE || kind == TKN_HEREDOC);
}

t_bool	is_out_redir_tkn(enum e_token_kind kind)
{
	return (kind == TKN_OUT_FILE || kind == TKN_APPEND_FILE);
}

t_bool	is_redir_token(enum e_token_kind kind)
{
	return (is_in_redir_tkn(kind) || is_out_redir_tkn(kind));
}

t_bool is_last_cmd(t_tree_node *cur_node)
{
	return (cur_node->prev == NULL || cur_node->prev->prev == NULL);
}
