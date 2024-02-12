/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:37:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/02/12 18:24:35 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"execute.h"

//export envpの+1でmalloc->copy。最後に指定の文字列を追加。
//char **export(char **envp, char *add_envvar)
//ok AAA=
//ko AAA

//unset envpの-1でmalloc->copy
//char **unset(char **envp, char *rm_envvar_name)
//環境変数にない文字列が来たら何もしない


size_t	count_strs_2(char **strs)
{
	size_t i;
	
	i = 0;
	while(strs[i] != NULL)
		i++;
	return (i);
}

char **init_envp(void)
{
	extern char **environ;
	char	**new_envp;
	size_t	i;
	size_t	j;
	size_t	str_count;

	str_count = count_strs_2(environ);
	new_envp = (char **)ft_xmalloc((str_count + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while(i < str_count)
	{
		new_envp[i++] = ft_xstrdup(environ[j]);
		j++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

t_manager init(void)
{
	t_manager manager;	

	manager.envp = init_envp();
	manager.exit_status = 0;
	manager.prev_output_fd = STDIN_FILENO;
	return (manager);
}
