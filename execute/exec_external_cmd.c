/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:06:02 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/26 18:46:29 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

static char	*search_cmd_path(char *cmd_name, char **path_list)
{
	size_t	i;
	char	*cmd_path;

	i = 0;
	while (path_list[i] != NULL)
	{
		cmd_path = join_and_free_str2(path_list[i], ft_xstrjoin("/", cmd_name));
		if (access(cmd_path, F_OK) == EXIST && !opendir(cmd_path))
		{
			free_multi_strs(path_list);
			return (cmd_path);
		}
		else
			free(cmd_path);
		i++;
	}
	free_multi_strs(path_list);
	return (NULL);
}

static char	*make_cmd_path(char *cmd_name, t_manager *manager)
{
	char	**path_list;
	char	*cmd_path;

	path_list = ft_xsplit(ms_getenv("PATH", manager), ':');
	if (path_list != NULL)
	{
		cmd_path = search_cmd_path(cmd_name, path_list);
		if (cmd_path)
			return (cmd_path);
	}
	if (access(cmd_name, F_OK) == EXIST && !opendir(cmd_name))
		return (cmd_name);
	return (NULL);
}

void	exec_external_cmd(char **cmd_args, t_manager *manager)
{
	char		*cmd_path;

	if (ft_strchr(cmd_args[0], '/'))
	{
		if (opendir(cmd_args[0]))
			perror_arg2_and_exit(cmd_args[0], "Is a directory", 126);
		if (access(cmd_args[0], F_OK) != EXIST)
			perror_arg2_and_exit(cmd_args[0], "No such file or directory", 127);
		ft_xexecve(cmd_args[0], cmd_args, manager->env_list);
	}
	cmd_path = make_cmd_path(cmd_args[0], manager);
	if (cmd_path == NULL)
		perror_arg2_and_exit(cmd_args[0], "command not found", 127);
	ft_xexecve(cmd_path, cmd_args, manager->env_list);
}
