/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnad_env_in_dquote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:26:32 by toshi             #+#    #+#             */
/*   Updated: 2024/04/19 03:07:37 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../utils/utils.h"
#include "../token_tozeki/tokenize.h"

t_bool is_envname_and_set_len(char *ptr, size_t *envname_len)
{
	ssize_t env_len;

	if (*ptr == '$')
	{
		env_len = count_dollar_last(ptr);
		if (env_len <= 1)
			return (FALSE);
		*envname_len = env_len - 1;
		return (TRUE);
	}
	return (FALSE);
}

static size_t _strlen_env_expanded(char *str, t_manager *manager)
{
	size_t len;
	char *env_val;
	size_t envname_len;

	len = 0;
	while (*str)
	{
		if (is_envname_and_set_len(str, &envname_len))
		{
			env_val = getenv_in_str(str, envname_len, manager);
			if (env_val)
				len += ft_strlen(env_val);
			str += sizeof(char) * envname_len;
		}
		else
			len++;
		str++;
	}
	return (len);
}

static size_t _strlcat_env_expanded(char *dest, char *str, size_t len, t_manager *manager)
{
	size_t dest_i;
	char *env_val;
	size_t envname_len;

	dest_i = 0;
	while (*str && dest_i < len)
	{
		if (is_envname_and_set_len(str, &envname_len))
		{
			env_val = getenv_in_str(str, envname_len, manager);
			if (env_val)
				dest_i += strlcat_ret_catlen(dest, env_val, len);
			str += sizeof(char) * envname_len;
		}
		else
			dest[dest_i++] = *str;
		str++;
	}
	dest[dest_i] = '\0';
	return (dest_i);
}

/// @brief  文字列にENVが見つかれば、引数のstrをfreeして、新しいstringを返す
char	*expand_env_in_dquote(char *str, t_manager *manager)
{
	size_t expanded_len;
	char *expanded_str;

	if (str == NULL)
		return (NULL);
	expanded_len = _strlen_env_expanded(str, manager);
	expanded_str = (char *)ft_xmalloc(sizeof(char) * (expanded_len + 1));
	_strlcat_env_expanded(expanded_str, str, (expanded_len + 1), manager);
	free(str);
	return (expanded_str);
}