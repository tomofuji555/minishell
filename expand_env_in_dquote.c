/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_in_dquote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:59 by toshi             #+#    #+#             */
/*   Updated: 2024/01/26 10:34:54 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static size_t _strlen_env_expanded(char *str)
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

static size_t _strlcat_env_expanded(char *dest, char *str, size_t len)
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
				dest_i += ft2_strlcat(dest, env_val, len);
			str += (sizeof(char) * (count_envname(str)));
		}
		else
			dest[dest_i++] = *str;
		str++;
	}
	dest[dest_i] = '\0';
	return (dest_i);
}

//文字列にENVが見つかれば、引数のstrをfreeして、新しいstringを返す
char *expand_env_in_dquote(char *str)
{
	size_t expanded_len;
	char *expanded_str;

	if (str == NULL)
		return (NULL);
	expanded_len = _strlen_env_expanded(str) + 1;
	if (expanded_len  == ft_strlen(str) + 1)
		return (str);
	expanded_str = (char *)ft_xmalloc(sizeof(char) * expanded_len);
	_strlcat_env_expanded(expanded_str, str, expanded_len);
	free(str);
	return (expanded_str);
}