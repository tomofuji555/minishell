/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:41:57 by toshi             #+#    #+#             */
/*   Updated: 2024/04/25 16:50:26 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "../minishell.h"
#include "../utils/utils.h"
#include "../libft/libft.h"

static t_bool	is_valuable_token_for_mode(enum e_mode mode, enum e_token_kind kind)
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

static void	update_mode_and_flag(enum e_token_kind kind, enum e_mode *mode, t_bool *flag)
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

// ver2
// t_bool	validate_syntax(t_token *ptr)
// {
// 	enum e_mode	mode;
// 	t_bool		flag;
	
// 	mode = MODE_FIRST;
// 	flag = FALSE;
// 	while (ptr != NULL)	
// 	{
// 		if (is_valuable_token_for_mode(mode, ptr->kind))
// 			flag = TRUE;
// 		if (ptr->kind == TKN_PIPE || is_redir_tkn (ptr->kind))
// 		{
// 			if (!evaluate(ptr, mode, flag))
// 				return (print_err_and_ret_false(ptr->val));
// 			update_mode_and_reset_flag(ptr, &mode, &flag);
// 		}
// 		ptr = ptr->next;
// 	}
// 	if (!flag && (mode == MODE_PIPE || mode == MODE_REDIR))
// 		return (print_err_and_ret_false("newline"));
// 	return (TRUE);
// }

//ver1
// t_bool	validate_syntax(t_token *ptr)
// {
// 	enum e_mode	mode;
// 	t_bool		flag;
	
// 	mode = MODE_FIRST;
// 	flag = FALSE;
// 	while (ptr != NULL)	
// 	{
// 		if (is_flag(mode, ptr->kind))
// 			flag = TRUE;
// 		if (ptr->kind == TKN_PIPE && mode == MODE_FIRST && !flag)
// 			return (print_err_and_ret_false(ptr->val));
// 		if (ptr->kind == TKN_PIPE && mode == MODE_PIPE && !flag)
// 			return (print_err_and_ret_false(ptr->val));
// 		if ((ptr->kind == TKN_PIPE || is_redir_tkn(ptr->kind)) && mode == MODE_REDIR && !flag)
// 			return (print_err_and_ret_false(ptr->val));
// 		update_mode_and_flag(ptr, &mode, &flag);
// 		ptr = ptr->next;
// 	}
// 	if (!flag && (mode == MODE_PIPE || mode == MODE_REDIR))
// 		return (print_err_and_ret_false("newline"));
// 	return (TRUE);
// }

// static t_bool	print_err_and_ret_false(char *val)
// {
// 	ft_putstr_fd("syntax error near unexpected token '", STDERR_FILENO);
// 	ft_putstr_fd(val, STDERR_FILENO);
// 	ft_putendl_fd("'", STDERR_FILENO);
// 	return (FALSE);
// }

// /// @brief 
// /// @param ptr 
// /// @param  
// /// @param flag 
// /// @return 
// static t_bool evaluate(t_token *ptr, enum e_mode mode, t_bool flag)
// {
// 	if (flag)
// 		return (TRUE);
// 	if (mode == MODE_REDIR \
// 		&& (ptr->kind == TKN_PIPE || is_redir_tkn(ptr->kind)))
// 		return (FALSE);
// 	if (mode == MODE_FIRST && ptr->kind == TKN_PIPE)
// 		return (FALSE);
// 	if (mode == MODE_PIPE && ptr->kind == TKN_PIPE)
// 		return (FALSE);
// 	return (TRUE);
// }