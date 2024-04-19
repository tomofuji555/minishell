/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libftwrap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 06:28:47 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/19 20:43:09 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

//malloc失敗したら、exitするだけのft_strtrim
//s1がNULLのときの対応追加
char	*ft_xstrdup(const char *s1)
{
	char *str;

	if (!s1)
		return (NULL);
	str = ft_strdup(s1);
	if (!str)
		perror_and_exit("malloc", 1);
	return (str);
}

// static size_t	get_start_count(const char *s1, const char *set)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
// 		i++;
// 	return (i);
// }

// static size_t	get_end_count(const char *s1, const char *set, size_t start)
// {
// 	size_t	len;

// 	len = ft_strlen(s1);
// 	while (len > start && ft_strchr(set, s1[len -1]) != NULL)
// 		len--;
// 	return (len - 1);
// }

//malloc失敗したら、exitするだけのft_strtrim
char	*ft_xstrtrim(const char *s1, const char *set)
{
	char *trimed_str;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	trimed_str = ft_strtrim(s1, set);
	if (!trimed_str)
		perror_and_exit("malloc", 1);
	return (trimed_str);
}

//malloc失敗したら、exitするだけのft_substr
//ここのNULLリターンは必要か審議->今のところs=NULLのパターンはない
char	*ft_xsubstr(const char *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = ft_substr(s, start, len);
	if (!str)
		perror_and_exit("malloc", 1);
	return (str);
}

//ここのNULLリターンは必要か審議->必要
char	*ft_xstrjoin(const char *s1, const char *s2)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = ft_strjoin(s1, s2);
	if (!str)
		perror_and_exit("malloc", 1);
	return (str);
}

char	*ft_xitoa(int n)
{
	char	*str;
	
	str = ft_itoa(n);
	if (str == NULL)
		perror_and_exit("malloc", 1);
	return (str);
}