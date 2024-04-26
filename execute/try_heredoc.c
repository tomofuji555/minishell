/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:49 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 18:48:36 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include "../libft/libft.h"
#include "../utils/utils.h"
#include "../expansion/expansion.h"

static void	_handle_sigint_in_heredoc(int num)
{
	g_signal_flag = 128 + num;
	ft_xclose(STDIN_FILENO);
}

static void	run_heredoc_helper(int fd, t_redir *ptr, t_manager *manager)
{
	char	*line;

	while (g_signal_flag == 0)
	{
		line = readline("> ");
		manager->heredoc_line++;
		if (line == NULL)
		{
			if (g_signal_flag == 0)
				perror_eof_in_heredoc(manager, ptr->val);
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

static char	*run_heredoc(t_redir *ptr, t_manager *manager)
{
	char	*path;
	int		fd;

	path = create_tmpfile_path();
	fd = open(path, O_WRONLY | O_CREAT, S_IRWXU);
	if (fd == SYS_FAILURE)
		perror_and_exit("open", 1);
	run_heredoc_helper(fd, ptr, manager);
	free(ptr->val);
	ft_xclose(fd);
	return (path);
}

static void	try_heredoc_helper(t_redir *redir_ptr, t_manager *manager)
{
	while (redir_ptr != NULL && g_signal_flag == 0)
	{
		if (redir_ptr->kind == REDIR_HEREDOC \
			|| redir_ptr->kind == REDIR_HEREDOC_NO_EXPAND)
			redir_ptr->val = run_heredoc(redir_ptr, manager);
		redir_ptr = redir_ptr->next;
	}
}

void	try_heredoc(t_tree_node *ptr, t_manager *manager)
{
	signal(SIGINT, _handle_sigint_in_heredoc);
	while (ptr->left != NULL)
		ptr = ptr->left;
	try_heredoc_helper(ptr->adv_data.infile_paths, manager);
	while (ptr != NULL)
	{
		if (ptr->right != NULL)
			try_heredoc_helper(ptr->right->adv_data.infile_paths, manager);
		ptr = ptr->prev;
	}
}
