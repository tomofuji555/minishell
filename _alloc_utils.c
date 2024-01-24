/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _alloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:26 by toshi             #+#    #+#             */
/*   Updated: 2024/01/16 20:34:20 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void *ft_xmalloc(size_t size)
{
	void *ret;

	if (size == 0)
		return(NULL);
	ret = (void *)malloc(size);
	if (ret == NULL)
		perror_and_exit("malloc", 1);
	return (ret);
}

void *ft_xrealloc(void *ptr, size_t size)
{
	if (ptr != NULL)
		free(ptr);
	if (size == 0)
		return (NULL);
	return (ft_xmalloc(size));
}

void *ft_xcalloc(size_t count, size_t size)
{
	void *ret;

	if (count == 0 || size == 0)
		return (NULL);
	ret = (void *)malloc(size);
	if (ret == NULL)
		perror_and_exit("malloc", 1);
	ft_memset(ret, '\0', count * size);
	return (ret);
}