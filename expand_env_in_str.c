/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_in_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:59 by toshi             #+#    #+#             */
/*   Updated: 2023/12/31 00:13:01 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

size_t	count_envname(char *dollar_ptr)
{
	char *ptr;
	size_t i;

	ptr = ++dollar_ptr;
	if (*ptr == '?' || *ptr == '$')
		return (1);
	i = 0;
	while(ptr[i] != '\0' && ft_isalpha(ptr[i]))
		i++;
	return (i);
}


char *search_env_val(char *dollar_ptr, size_t env_name_len)
{
	char *env_name;
	char *env_val;

	env_name = ft_substr(++dollar_ptr, 0, env_name_len);
	if (env_name == NULL)
		perror_and_exit("malloc", 1);
	env_val = ft_getenv(env_name);
	free(env_name);
	return (env_val);
}

size_t	ms_strlcat(char *dest, const char *src, size_t size)
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

size_t strlen_env_expanded(char *str)
{
	size_t len;
	char *env_val;

	len = 0;
	while(*str)
	{
		if (*str == '$' && count_envname(str))
		{
			env_val = search_env_val(str, count_envname(str));
			if (env_val)
				len += ft_strlen(env_val);
			str += (sizeof(char) * (count_envname(str)));
		}
		else
			len++;
		str++;
	}
	return (len);
}

size_t strlcat_env_expanded(char *dest, char *str, size_t len)
{
	size_t dest_i;
	char *env_val;

	dest_i = 0;
	while(*str && dest_i < len)
	{
		if(*str == '$' && count_envname(str))
		{
			env_val = search_env_val(str, count_envname(str));
			if (env_val)
				dest_i += ms_strlcat(dest, env_val, len);
			str += (sizeof(char) * (count_envname(str)));
		}
		else
			dest[dest_i++] = *str;
		str++;
	}
	dest[dest_i] = '\0';
	return (dest_i);
}

char *expand_env_in_str(char *str)
{
	size_t len;
	char *expanded_str;

	if (str == NULL)
		return (NULL);
	len = 1 + strlen_env_expanded(str);
	if (len  == ft_strlen(str) + 1)
		return (str);
	expanded_str = (char *)ft_xmalloc(sizeof(char) * len);
	strlcat_env_expanded(expanded_str, str, len);
	free(str);
	return (expanded_str);
}