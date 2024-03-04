/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:59 by toshi             #+#    #+#             */
/*   Updated: 2024/03/05 00:55:26 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

//NULLが帰ってくるときの対応を考えないといけない
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
	dest[dest_len + i] = '\0';
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

char *join_and_free_str2(char *str1, char *str2)
{
	char *joined_str;

	joined_str = ft_xstrjoin(str1, str2);
	free(str2);
	return (joined_str);
}


