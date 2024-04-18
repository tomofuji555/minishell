/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_heredoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:13:08 by toshi             #+#    #+#             */
/*   Updated: 2024/04/18 20:44:01 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include "../utils/utils.h"
#include "../expansion/expansion.h"

//ULLMAX通り以上のファイルを作成されるとエラー
static char	*_create_tmpfile_path(void)
{
	unsigned long long num;
	char *path;

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

static void	_perror_eof_in_heredoc(t_manager *manager, char *delim)
{
	ft_putstr_fd("warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(manager->heredoc_line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted \'", STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putstr_fd("\')\n", STDERR_FILENO);
}

static void _accept_lines(int fd, t_redir *ptr, t_manager *manager)
{
	char	*line;

	while (signal_flag == 0)
	{
		line = readline("> ");
		manager->heredoc_line++;
		if (line == NULL)
		{
			if (signal_flag == 0)
				_perror_eof_in_heredoc(manager, ptr->val);
			break ;
		}
		else if (is_equal_str(line, ptr->val))
		{
			free(line);
			break ;
		}
		if (ptr->kind != REDIR_HEREDOC_NO_EXPAND)
			line = expand_env_in_dquote(line, manager);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

//heredocで書き込んだファイルのpathを返す
//delimのfreeは無し->delimをfreeしないとリークする
// static char	*run_heredoc(char *delim, enum e_redir_kind kind, t_manager *manager)
char	*run_heredoc(t_redir *ptr, t_manager *manager)
{
	char	*path;
	int		fd;

	path = _create_tmpfile_path();
	fd = open(path, O_WRONLY | O_CREAT, S_IRWXU);
	if (fd == SYS_FAILURE)
		perror_and_exit("open", 1);
	_accept_lines(fd, ptr, manager);
	free(ptr->val);
	ft_xclose(fd);
	return (path);
}

/// @brief ctrl+cで終了した時、heredocのdelimと同じ名前のファイルを消してしまうため、
///	exitする可能性があるため、accessを噛ませることにした
void	remove_heredoc_tmpfile(t_tree_node *tnode_head)
{
	t_tree_node *ptr;
	t_redir	*redir_ptr;

	ptr = tnode_head;
	while (ptr != NULL)
	{
		redir_ptr = ptr->adv_data.infile_paths;
		while (redir_ptr != NULL)
		{
			if ((redir_ptr->kind == REDIR_HEREDOC || \
				redir_ptr->kind == REDIR_HEREDOC_NO_EXPAND) \
				&& ft_strnstr(redir_ptr->val, "/tmp/", 6))
				unlink(redir_ptr->val);
			redir_ptr = redir_ptr->next;
		}
		ptr = ptr->right;
	}
}