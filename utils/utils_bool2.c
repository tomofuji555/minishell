/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bool2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:48:39 by toshi             #+#    #+#             */
/*   Updated: 2024/04/19 20:49:54 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	is_valuable_token(enum e_token_kind kind)
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

t_bool	is_redir_tkn(enum e_token_kind kind)
{
	return (is_in_redir_tkn(kind) || is_out_redir_tkn(kind));
}
