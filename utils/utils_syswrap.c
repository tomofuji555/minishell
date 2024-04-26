/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syswrap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:14:55 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/26 18:54:57 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../libft/libft.h"

void	*ft_xmalloc(size_t size)
{
	void	*ret;

	if (size == 0)
		return (NULL);
	ret = (void *)malloc(size);
	if (ret == NULL)
		perror_and_exit("malloc", 1);
	return (ret);
}

void	*ft_xrealloc(void *ptr, size_t size)
{
	if (ptr != NULL)
		free(ptr);
	if (size == 0)
		return (NULL);
	return (ft_xmalloc(size));
}

void	*ft_xcalloc(size_t count, size_t size)
{
	void	*ret;

	if (count == 0 || size == 0 || size > SIZE_MAX / count)
		return (NULL);
	ret = ft_calloc(count, size);
	if (ret == NULL)
		perror_and_exit("malloc", 1);
	return (ret);
}

int	ft_xdup(int copied_fd)
{
	int	dest_fd;

	dest_fd = dup(copied_fd);
	if (dest_fd == SYS_FAILURE)
		perror_and_exit("dup", 1);
	return (dest_fd);
}

int	ft_xdup2(int copied_fd, int dest_fd)
{
	if (dup2(copied_fd, dest_fd) == SYS_FAILURE)
		perror_and_exit("dup2", 1);
	return (dest_fd);
}
