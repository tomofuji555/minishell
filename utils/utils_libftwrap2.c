/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libftwrap2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:37:54 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 21:49:56 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

//ここのNULLリターンは必要か審議->make_cmdで必要
char	**ft_xsplit(const char *s, char c)
{
	char	**strs;

	if (s == NULL)
		return (NULL);
	strs = ft_split(s, c);
	if (!strs)
		perror_and_exit("malloc", 1);
	return (strs);
}
