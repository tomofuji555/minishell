/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:41:57 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 19:31:32 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "../minishell.h"
#include "../utils/utils.h"
#include "../libft/libft.h"

static t_bool	is_valuable_token_for_mode(enum e_mode mode, \
	enum e_token_kind kind)
{
	if (mode == MODE_REDIR && is_valuable_token(kind))
		return (TRUE);
	if ((mode == MODE_FIRST || mode == MODE_PIPE) \
		&& (is_valuable_token(kind) || is_redir_tkn(kind)))
		return (TRUE);
	return (FALSE);
}

static t_bool	evaluate(enum e_token_kind kind, enum e_mode mode, t_bool flag)
{
	if (is_redir_tkn(kind) && mode == MODE_REDIR && !flag)
		return (FALSE);
	if (kind == TKN_PIPE && !flag)
		return (FALSE);
	return (TRUE);
}

static t_bool	print_syntax_error_and_ret_false(char *val)
{
	ft_putstr_fd("syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(val, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (FALSE);
}

static void	update_mode_and_flag(enum e_token_kind kind, \
	enum e_mode *mode, t_bool *flag)
{
	if (is_redir_tkn(kind))
	{
		*mode = MODE_REDIR;
		*flag = FALSE;
		return ;
	}
	if (kind == TKN_PIPE)
	{
		*mode = MODE_PIPE;
		*flag = FALSE;
		return ;
	}
}

//	mode_first スペースを除いて最初にPIPEがあったらエラー
//	mode_pipe パイプから次のパイプ/NULLまでに、スペース以外のトークンがなければ、エラー
//	mode_redir リダイレクトから次のリダイレクト/パイプ/NULLまでに、スペース以外のトークンがなければ、エラー
//	パイプ/リダイレクトが来たときにそこまでのトークンを評価する->各モードに切り替える
t_bool	validate_syntax(t_token *ptr)
{
	enum e_mode	mode;
	t_bool		flag;

	mode = MODE_FIRST;
	flag = FALSE;
	while (ptr != NULL)
	{
		if (is_valuable_token_for_mode(mode, ptr->kind))
			flag = TRUE;
		if (!evaluate(ptr->kind, mode, flag))
			return (print_syntax_error_and_ret_false(ptr->val));
		update_mode_and_flag(ptr->kind, &mode, &flag);
		ptr = ptr->next;
	}
	if (!flag && (mode == MODE_PIPE || mode == MODE_REDIR))
		return (print_syntax_error_and_ret_false("newline"));
	return (TRUE);
}
