/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:59 by toshi             #+#    #+#             */
/*   Updated: 2024/01/16 20:15:42 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void perror_and_exit(char *err_title, int exit_status)
{
	perror(err_title);
	exit(exit_status);
}

//帰りがコピーしたカウントを返すft_strlcat
size_t	ft2_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;
	
	dest_len = ft_strlen(dest);
	if (size == 0 || size < dest_len)
		return (0);
	i = 0;
	while(src[i] != '\0' && i + 1 < size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else
		return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
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


static size_t	get_dig_nbase(unsigned long long num, unsigned int base)
{
	size_t	dig;

	dig = 1;
	while (num >= base)
	{
		num /= base;
		dig++;
	}
	return (dig);
}

char	*ulltonbase(unsigned long long num, unsigned int base)
{
	const char	*string_base = "0123456789ABCDEF";
	char		*str;
	size_t		dig;

	if (base > 16)
		return (NULL);
	dig = get_dig_nbase(num, base);
	str = (char *)ft_calloc((dig + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (dig > 0)
	{
		str[--dig] = string_base[num % base];
		num /= base;
	}
	return (str);
}

//malloc失敗したら、exitするだけのft_substr
char	*ft_xsubstr(const char *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*str;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (start > len_s)
		return (ft_xstrdup(""));
	if (len > len_s)
		len = len_s - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		perror_and_exit("malloc", 1);
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}

