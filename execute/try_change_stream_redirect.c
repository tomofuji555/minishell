/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_change_stream_redirect.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:17:33 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/20 17:27:29 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../utils/utils.h"

/// @brief openでエラーが起きた時、perrorでエラー文(No such file or
/// directory/Permission denied)を自動に振り分けてくれる
int	_open_redir_path(t_redir *ptr)
{
	int	fd;

	if (ptr->kind == REDIR_OUT_FILE)
		fd = open(ptr->val, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (ptr->kind == REDIR_APPEND_FILE)
		fd = open(ptr->val, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(ptr->val, O_RDONLY);
	if (fd == SYS_FAILURE)
		perror(ptr->val);
	return (fd);
}

static int	_find_last_fd(t_redir *redir_ptr)
{
	int	fd;

	fd = DEFAULT;
	while (redir_ptr != NULL)
	{
		if (fd != DEFAULT)
			ft_xclose(fd);
		fd = _open_redir_path(redir_ptr);
		if (fd == SYS_FAILURE)
			return (fd);
		redir_ptr = redir_ptr->next;
	}
	return (fd);
}

/// @brief redir_headがNULLじゃない前提で実装
t_bool	try_change_stream_redirect(t_redir *redir_head, int dest_fd)
{
	int	redir_fd;

	redir_fd = _find_last_fd(redir_head);
	if (redir_fd == SYS_FAILURE)
		return (FALSE);
	ft_xdup2 (redir_fd, dest_fd);
	ft_xclose(redir_fd);
	return (TRUE);
}
