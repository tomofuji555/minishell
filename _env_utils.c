/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:04:36 by toshi             #+#    #+#             */
/*   Updated: 2024/03/05 02:45:51 by tozeki           ###   ########.fr       */
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
char	*ft_getenv(const char *env_name)
{
	extern char	**environ;
	char		*key;
	size_t		i;

	if (is_equal_str(env_name, "?"))
		;//終了ステータスを返す
	i = 0;
	while (environ[i] != NULL)
	{
		key = ft_xsubstr(environ[i], 0, (size_t)(ft_strchr(environ[i], '=') - environ[i]));
		if (is_equal_str(env_name, key))
		{
			free(key);
			return (ft_strchr(environ[i], '=') + sizeof(char));
		}
		free(key);
		i++;
	}
	return (NULL);
}


//char *ft_getenv_ver2(const char *env_name, t_env_node *head)
//{
//	t_env_node	*ptr;

//	ptr = head;
//	while (ptr != NULL)
//	{
//		if (is_equal_str(env_name, ptr->key))
//			return (ptr->val);
//		ptr = ptr->next;
//	}
//	return (NULL);
//}


char *getenv_in_str(char *dollar_ptr, size_t env_name_len)
{
	char *env_name;
	char *env_val;

	env_name = ft_xsubstr(++dollar_ptr, 0, env_name_len);
	env_val = ft_getenv(env_name);
	free(env_name);
	return (env_val);
}

