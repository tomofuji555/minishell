/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libftwrap2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:37:54 by toshi             #+#    #+#             */
/*   Updated: 2024/04/19 20:43:02 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

// static size_t	get_split_len(const char *s, char c)
// {
// 	size_t	len;
// 	size_t	i;

// 	len = 0;
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
// 			len++;
// 		i++;
// 	}
// 	return (len);
// }

// static char	**insert_strs(const char *s, char c, char **strs)
// {
// 	size_t	i;
// 	size_t	i_strs;
// 	size_t	len_j;

// 	i = 0;
// 	i_strs = 0;
// 	len_j = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
// 		{
// 			strs[i_strs] = ft_xsubstr(&s[i - len_j], 0, len_j + 1);
// 			i_strs++;
// 			len_j = 0;
// 		}
// 		else if (s[i] != c)
// 			len_j++;
// 		i++;
// 	}
// 	strs[i_strs] = NULL;
// 	return (strs);
// }

//ここのNULLリターンは必要か審議->make_cmdで必要
char	**ft_xsplit(const char *s, char c)
{
	size_t	len_i;
	char	**strs;

	if (s == NULL)
		return (NULL);
	strs = ft_split(s, c);
	if (!strs)
		perror_and_exit("malloc", 1);
	return (strs);
}