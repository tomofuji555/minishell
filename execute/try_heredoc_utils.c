/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_heredoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:13:08 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 19:02:47 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include "../libft/libft.h"
#include "../utils/utils.h"
#include "../expansion/expansion.h"

//ULLMAX通り以上のファイルを作成されるとエラー
char	*create_tmpfile_path(void)
{
	unsigned long long	num;
	char				*path;

	num = 0;
	while (num < ULLONG_MAX)
	{
		path = join_and_free_str2("/tmp/", ft_itoa(num++));
		if (access(path, F_OK) == NOT_EXIST)
			return (path);
		free (path);
	}
	perror_arg2("file_error", "unexpected number of files");
	exit(1);
}

void	perror_eof_in_heredoc(t_manager *manager, char *delim)
{
	ft_putstr_fd("warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(manager->heredoc_line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted \'", STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putstr_fd("\')\n", STDERR_FILENO);
}

/// @brief ctrl+cで終了した時、heredocのdelimと同じ名前のファイルを消す
///	可能性があるため、strnstrを噛ませ,tmp/のファイルか確認した
static void	remove_heredoc_tmpfile_helper(t_redir *redir_ptr)
{
	while (redir_ptr != NULL)
	{
		if ((redir_ptr->kind == REDIR_HEREDOC \
			|| redir_ptr->kind == REDIR_HEREDOC_NO_EXPAND) \
			&& ft_strnstr(redir_ptr->val, "/tmp/", 6))
			unlink(redir_ptr->val);
		redir_ptr = redir_ptr->next;
	}
}

void	remove_heredoc_tmpfile(t_tree_node *ptr)
{
	while (ptr->left != NULL)
		ptr = ptr->left;
	remove_heredoc_tmpfile_helper(ptr->adv_data.infile_paths);
	while (ptr != NULL)
	{
		if (ptr->right != NULL)
			remove_heredoc_tmpfile_helper(ptr->adv_data.infile_paths);
		ptr = ptr->prev;
	}
}
