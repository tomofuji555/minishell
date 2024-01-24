/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redir_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 03:40:09 by toshi             #+#    #+#             */
/*   Updated: 2024/01/16 20:35:17 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int _open_redir_path(t_redir *node)
{
	int fd;
	
	if (node->kind == REDIR_OUT_FILE)
		fd = open(node->val, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	else if (node->kind == REDIR_APPEND_FILE)
		fd = open(node->val, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	else
		fd = open(node->val, O_RDONLY);
	return (fd);
}

int _fd_find_last(t_redir *redir_ptr)
{
	int fd;

	fd = -1;
	while(redir_ptr->next != NULL)
	{
		if (fd > -1)
			close(fd);
		fd = _open_redir_path(redir_ptr);
		if (fd == SYS_FAILURE)
			return (fd);//error文吐く、exitするのは外
		redir_ptr = redir_ptr->next;
	}
	return (fd);
}

void	change_stream_to_redir(t_redir *redir_head, int dest_fd)
{
	int redir_fd;

	redir_fd = _fd_find_last(redir_head);
	if (redir_fd == SYS_FAILURE)
		;//FALSEを返す
	if (dup2(redir_fd, dest_fd) == SYS_FAILURE)
		;//exit
	if (close(redir_fd) == SYS_FAILURE)
		;//検討
}