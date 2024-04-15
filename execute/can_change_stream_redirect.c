/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_change_stream_redirect.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:17:33 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/15 20:18:16 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../utils/utils.h"

static int open_redir_path(t_redir *node)
{
	int fd;

	if (node->kind == REDIR_OUT_FILE)
		fd = open(node->val, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (node->kind == REDIR_APPEND_FILE)
		fd = open(node->val, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(node->val, O_RDONLY);
	if (fd == SYS_FAILURE)
		perror(node->val); //No such file or directory / Permission denied を勝手に吐いてくれる
	return (fd);
}

static int find_last_fd(t_redir *redir_ptr)
{
	int fd;

	fd = DEFAULT;
	while(redir_ptr != NULL)
	{
		if (fd != DEFAULT)
			ft_xclose(fd);
		fd = open_redir_path(redir_ptr);
		if (fd == SYS_FAILURE)
			return (fd);
		redir_ptr = redir_ptr->next;
	}
	return (fd);
}

//redir_headがNULLじゃない前提で実装
t_bool	can_change_stream_redirect(t_redir *redir_head, int dest_fd)
{
	int redir_fd;

	redir_fd = find_last_fd(redir_head);
	if (redir_fd == SYS_FAILURE)
		return (FALSE);
	ft_xdup2 (redir_fd, dest_fd);
	ft_xclose(redir_fd);
	return (TRUE);
}