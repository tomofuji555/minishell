/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:55:15 by toshi             #+#    #+#             */
/*   Updated: 2024/04/19 21:11:49 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

void	sort_envp(char **envp, size_t count)
{
	size_t aa;
	size_t bb;
	char *tmp;

	aa = 0;
	while (aa + 1 < count)
	{
		bb = 0;
		while (bb + 1 < count)
		{
			if (ft_strncmp(envp[bb], envp[bb + 1], ft_strlen(envp[bb])) > 0)
			{
				tmp = envp[bb];
				envp[bb] = envp[bb + 1];
				envp[bb + 1] = tmp;
			}
			bb++;
		}
		aa++;
	}
}

void print_sorted_env(t_env *env_list)
{
	char **envp;
	size_t count;
	size_t i;

	count = count_envvar(env_list);
	envp = make_envp(env_list);
	sort_envp(envp, count);
	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strnstr(envp[i], "_=", ft_strlen(envp[i])))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		}
		i++;
	}
	free_multi_strs(envp);
}