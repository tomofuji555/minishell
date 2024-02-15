/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:04:36 by toshi             #+#    #+#             */
/*   Updated: 2024/02/15 18:01:14 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

size_t	count_envname(char *dollar_ptr)
{
	char *ptr;
	size_t i;

	ptr = ++dollar_ptr;
	if (is_delim(*ptr))
		return (0);
	i = 0;
	while(ptr[i] != '\0' && ft_isalnum(ptr[i]))
		i++;
	return (i);
}

//envに必ず=がある前提で実装している
char	*ft_getenv(const char *target_str)
{
	extern char	**environ;
	char		*env_name;
	size_t		i;

	if (ft_strcmp(target_str, "?") == 0)
		;//終了ステータスを返す
	i = 0;
	while (environ[i] != NULL)
	{
		env_name = ft_xsubstr(environ[i], 0, (size_t)(ft_strchr(environ[i], '=') - environ[i]));
		if (ft_strcmp(target_str, env_name) == 0)
		{
			free(env_name);
			return (ft_strchr(environ[i], '=') + sizeof(char));
		}
		free(env_name);
		i++;
	}
	return (NULL);
}

char *search_env_val(char *dollar_ptr, size_t env_name_len)
{
	char *env_name;
	char *env_val;

	env_name = ft_xsubstr(++dollar_ptr, 0, env_name_len);
	env_val = ft_getenv(env_name);
	free(env_name);
	return (env_val);
}

