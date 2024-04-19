/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:04:36 by toshi             #+#    #+#             */
/*   Updated: 2024/04/19 20:33:25 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ms_getenv(const char *env_name, t_manager *manager)
{
	t_env	*ptr;

	if (is_equal_str(env_name, "?"))
		return (manager->exit_status);
	ptr = manager->env_list;
	while (ptr != NULL)
	{
		if (is_equal_str(env_name, ptr->key))
			return (ptr->val);
		ptr = ptr->next;
	}
	return (NULL);
}

t_env	*search_env(char *name, t_env *env_list)
{
	t_env	*ptr;
	t_env	*new;
	
	ptr = env_list;
	while (ptr != NULL)
	{
		if (is_equal_str(ptr->key, name))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

size_t	count_envvar(t_env *env_list)
{
	t_env	*ptr;
	size_t	count;

	count = 0;
	ptr = env_list;
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

char	**make_envp(t_env *env_list)
{
	char	**envp;
	t_env	*ptr;
	size_t	i;

	envp = (char **)ft_xmalloc(sizeof(char *) * (count_envvar(env_list) + 1));
	i = 0;
	ptr = env_list;
	while (ptr != NULL)
	{
		envp[i++] = join_and_free_str2(ptr->key, ft_xstrjoin("=", ptr->val));
		ptr = ptr->next;
	}
	envp[i] = NULL;
	return (envp);
}

