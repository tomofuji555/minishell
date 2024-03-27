/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:49 by toshi             #+#    #+#             */
/*   Updated: 2024/03/27 22:48:53 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	rm_heredoc_tmp(t_tree_node *tnode_head)
{
	t_tree_node *ptr;
	t_redir	*redir_ptr;

	ptr = tnode_head;
	while (ptr != NULL)
	{
		redir_ptr = ptr->refine_data.infile_paths;
		while (redir_ptr != NULL)
		{
			if (redir_ptr->kind == REDIR_HEREDOC || \
				redir_ptr->kind == REDIR_HEREDOC_NO_EXPAND)
				ft_xunlink(redir_ptr->val); //ctrl+cで終了した時、見つからないファイルを消そうとしてエラーし、exitする可能性あり
			redir_ptr = redir_ptr->next;
		}
		ptr = ptr->right;
	}
}

//ULLMAX通り以上のファイルを作成されるとエラー
static char	*create_tmpfile_path(void)
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

//kindがREDIR_HEREDOC_NO_EXPANDでなければEXPAND
//putし、そのlineをfree
static void output_fd_and_free_line(int fd, char *line, enum e_redir_kind heredoc_kind, t_manager manager)
{
	if (heredoc_kind == REDIR_HEREDOC)
		line = expand_env_in_dquote(line, manager);
	ft_putendl_fd(line, fd);
	free(line);
}

//heredocで書き込んだファイルのpathを返す
//delimのfreeは無し->delimをfreeしないとリークする
static char	*run_heredoc(char *delim, enum e_redir_kind heredoc_kind, t_manager manager)
{
	char	*line;
	char	*path;
	int		fd;

	path = create_tmpfile_path();
	fd = open(path, O_WRONLY | O_CREAT, S_IRWXU);
	if (fd == SYS_FAILURE)
		perror_and_exit("open", 1);
	while (signal_flag == 0)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (is_equal_str(line, delim))
		{
			free(line);
			break;
		}
		output_fd_and_free_line(fd, line, heredoc_kind, manager);
	}
	free(delim);
	ft_xclose(fd);
	return (path);
}

void handle_sigint_in_heredoc(int num)
{
	signal_flag = 128 + num;
}

void	try_heredoc(t_tree_node *tnode_head, t_manager manager)
{
	t_tree_node *ptr;
	t_redir	*redir_ptr;

	signal(SIGINT, handle_sigint_in_heredoc);
	ptr = tnode_head;
	while (ptr != NULL && signal_flag == 0)
	{
		redir_ptr = ptr->refine_data.infile_paths;
		while (redir_ptr != NULL && signal_flag == 0)
		{
			if (redir_ptr->kind == REDIR_HEREDOC || \
				redir_ptr->kind == REDIR_HEREDOC_NO_EXPAND)
				redir_ptr->val = run_heredoc(redir_ptr->val, redir_ptr->kind, manager);
			redir_ptr = redir_ptr->next;
		}
		ptr = ptr->right;
	}
}
