/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bool_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:09 by toshi             #+#    #+#             */
/*   Updated: 2024/02/23 23:09:09 by tozeki           ###   ########.fr       */
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

t_bool is_valuable_tkn(enum e_token_kind kind)
{
	return (kind == TKN_TEXT || kind == TKN_S_QUOTE \
		|| kind == TKN_D_QUOTE || kind == TKN_ENV);
}

t_bool	is_redir_tkn(enum e_token_kind kind)
{
	return (is_in_redir_tkn(kind) || is_out_redir_tkn(kind));
}

t_bool	is_in_redir_tkn(enum e_token_kind kind)
{
	return (kind == TKN_IN_FILE || kind == TKN_HEREDOC);
}

t_bool	is_out_redir_tkn(enum e_token_kind kind)
{
	return (kind == TKN_OUT_FILE || kind == TKN_APPEND_FILE);
}

t_bool is_last_cmd(t_tree_node *ptr)
{
	return (ptr->right == NULL);
	//return (ptr->prev == NULL || ptr->prev->prev == NULL);
}

t_bool is_first_cmd(t_tree_node *ptr)
{
	return (ptr->left == NULL && (ptr->prev == NULL || ptr->prev->right != ptr));
}

t_bool	is_cmd_node(t_tree_node *ptr)
{
	return (ptr->exec_data.cmd_args || ptr->exec_data.infile_paths || ptr->exec_data.outfile_paths);
	//return (ptr->left == NULL && ptr->right == NULL);
}