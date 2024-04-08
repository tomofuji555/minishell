/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:59 by toshi             #+#    #+#             */
/*   Updated: 2024/04/08 12:18:09 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//static size_t	get_dig_nbase(unsigned long long num, unsigned int base)
//{
//	size_t	dig;

//	dig = 1;
//	while (num >= base)
//	{
//		num /= base;
//		dig++;
//	}
//	return (dig);
//}

////NULLが帰ってくるときの対応を考えないといけない
//char	*ulltonbase(unsigned long long num, unsigned int base)
//{
//	const char	*string_base = "0123456789ABCDEF";
//	char		*str;
//	size_t		dig;

//	if (base > 16)
//		return (NULL);
//	dig = get_dig_nbase(num, base);
//	str = (char *)ft_calloc((dig + 1), sizeof(char));
//	if (str == NULL)
//		return (NULL);
//	while (dig > 0)
//	{
//		str[--dig] = string_base[num % base];
//		num /= base;
//	}
//	return (str);
//}

size_t	count_strs(char **strs)
{
	size_t i;

	i = 1;
	while (strs[i] != NULL)
		i++;
	return (i);
}

//帰りがコピーしたカウントを返すft_strlcat
size_t	strlcat_ret_catlen(char *dest, const char *src, size_t size)
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
	dest[dest_len + i] = '\0';
	return (i);
}

char *join_and_free_str2(char *str1, char *str2)
{
	char *joined_str;

	joined_str = ft_xstrjoin(str1, str2);
	free(str2);
	return (joined_str);
}

char *join_and_free_str1(char *str1, char *str2)
{
	char *joined_str;

	joined_str = ft_xstrjoin(str1, str2);
	free(str1);
	return (joined_str);
}

//int	ft_strcmp(const char *s1, const char *s2)
//{
//	size_t	i;

//	i = 0;
//	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
//		i++;
//	if (s1[i] == '\0' && s2[i] == '\0')
//		return (0);
//	else
//		return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
//}


char *strchr_n_back(char *str, char c, size_t n)
{
	size_t	c_count;
	size_t	len;

	if (n == 0)
		return (NULL);
	c_count = 0;
	len = ft_strlen(str);
	while (len && n > c_count)
	{
		if (str[len - 1] == c)
			c_count++;
		len--;
	}
	if (n == c_count)
		return (&(str[len - 1]));
	return (NULL);
}

void update_exit_status(t_manager *manger, int num) //xitoaにする必要がある
{
	free(manger->exit_status);
	manger->exit_status = ft_itoa(num);
}

