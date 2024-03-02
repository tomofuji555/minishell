/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _libftwrap_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 06:28:47 by tozeki            #+#    #+#             */
/*   Updated: 2024/03/02 11:24:33 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	perror_arg2(char *err_target, char *err_str)
{
	ft_putstr_fd(err_target, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(err_str, STDERR_FILENO);
}

void	perror_arg2_and_exit(char *err_target, char *err_str, int exit_status)
{
	perror_arg2(err_target, err_str);
	exit(exit_status);
}

void perror_and_exit(char *err_target, int exit_status)
{
	perror(err_target);
	exit(exit_status);
}

//malloc失敗したら、exitするだけのft_strtrim
char	*ft_xstrdup(const char *s1)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s1) + 1;
	str = (char *)ft_xmalloc(sizeof(char) * len);
	ft_strlcpy(str, s1, len);
	return (str);
}

static size_t	get_start_count(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	return (i);
}

static size_t	get_end_count(const char *s1, const char *set, size_t start)
{
	size_t	len;

	len = ft_strlen(s1);
	while (len > start && ft_strchr(set, s1[len -1]) != NULL)
		len--;
	return (len - 1);
}

//malloc失敗したら、exitするだけのft_strtrim
char	*ft_xstrtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char *trimed_str;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	start = get_start_count(s1, set);
	end = get_end_count(s1, set, start);
	if (start > end)
		return (ft_xstrdup(""));
	trimed_str = ft_substr(&s1[start], 0, end - start + 1);
	if (trimed_str == NULL)
		perror_and_exit("malloc", 1);
	return (trimed_str);
}

//malloc失敗したら、exitするだけのft_substr
char	*ft_xsubstr(const char *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*str;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < start)
		return (ft_xstrdup(""));
	if (len_s < len)
		len = len_s - start;
	str = (char *)ft_xmalloc(sizeof(char) * (len + 1));
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}

char	*ft_xstrjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)ft_xcalloc(len, sizeof(char));
	ft_strlcpy(str, s1, len);
	ft_strlcat(str, s2, len);
	return (str);
}

static size_t	get_split_len(const char *s, char c)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			len++;
		i++;
	}
	return (len);
}

static char	**insert_strs(const char *s, char c, char **strs)
{
	size_t	i;
	size_t	i_strs;
	size_t	len_j;

	i = 0;
	i_strs = 0;
	len_j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			strs[i_strs] = ft_xsubstr(&s[i - len_j], 0, len_j + 1);
			i_strs++;
			len_j = 0;
		}
		else if (s[i] != c)
			len_j++;
		i++;
	}
	strs[i_strs] = NULL;
	return (strs);
}

char	**ft_xsplit(const char *s, char c)
{
	size_t	len_i;
	char	**strs;

	if (s == NULL)
		return (NULL);
	len_i = get_split_len(s, c) + 1;
	//strs = (char **)ft_xcalloc(sizeof(char *) * (get_split_len(s, c) + 1));
	strs = (char **)ft_xmalloc(sizeof(char *) * len_i); //ft_xcallocが原因　xmalloc/callocならいける
	return (insert_strs(s, c, strs));
}