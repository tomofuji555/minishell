/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:49 by toshi             #+#    #+#             */
/*   Updated: 2024/04/08 23:02:53 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//ctrl+cで終了した時、見つからないファイルを消そうとしてxunlinkがエラーし、exitする可能性があるため、accessを噛ませることにした
void	remove_file(char *path)
{
	if (access(path, F_OK) == EXIST) //ft_strnstr(path, "/tmp/", 5) && 
		ft_xunlink(path);
}

void	rm_heredoc_tmp(t_tree_node *tnode_head)
{
	t_tree_node *ptr;
	t_redir	*redir_ptr;

	ptr = tnode_head;
	while (ptr != NULL)
	{
		redir_ptr = ptr->adv_data.infile_paths;
		while (redir_ptr != NULL)
		{
			if (redir_ptr->kind == REDIR_HEREDOC || \
				redir_ptr->kind == REDIR_HEREDOC_NO_EXPAND)
				remove_file(redir_ptr->val);
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
static void output_fd_and_free_line(int fd, char *line, enum e_redir_kind heredoc_kind, t_manager *manager)
{
	if (heredoc_kind == REDIR_HEREDOC)
		line = expand_env_in_dquote(line, manager);
	ft_putendl_fd(line, fd);
	free(line);
}

void	perror_eof_in_heredoc(t_manager *manager, char *delim)
{
	ft_putstr_fd("warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(manager->heredoc_line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted \'", STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putstr_fd("\')\n", STDERR_FILENO);
}

//heredocで書き込んだファイルのpathを返す
//delimのfreeは無し->delimをfreeしないとリークする
static char	*run_heredoc(char *delim, enum e_redir_kind heredoc_kind, t_manager *manager)
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
		manager->heredoc_line++;
		if (line == NULL)
		{
			perror_eof_in_heredoc(manager, delim);
			break ;
		}
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
	ft_xclose(STDIN_FILENO);
}

void	try_heredoc(t_tree_node *tnode_head, t_manager *manager)
{
	t_tree_node *ptr;
	t_redir	*redir_ptr;

	signal(SIGINT, handle_sigint_in_heredoc);
	ptr = tnode_head;
	while (ptr != NULL && signal_flag == 0)
	{
		redir_ptr = ptr->adv_data.infile_paths;
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
