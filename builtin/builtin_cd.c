/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:54:15 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/20 17:52:57 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

void	update_current_dir(t_manager *manager, char *path_slash)
{
	char	*new_current_dir;
	char	*new_pwd;

	free(manager->current_dir);
	new_current_dir = ft_xsubstr(path_slash, 0, ft_strlen(path_slash) - 1);
	manager->current_dir = new_current_dir;
	new_pwd = ft_xstrjoin("PWD=", new_current_dir);
	upsert_env(manager, new_pwd);
	free(new_pwd);
}

t_bool	try_cd_home(t_manager *manager)
{
	char	*path_slash;

	path_slash = ft_xstrjoin(ms_getenv("HOME", manager), "/");
	if (path_slash == NULL)
	{
		perror_arg2("cd", "HOME not set");
		return (FALSE);
	}
	if (chdir(path_slash) == SYS_FAILURE)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(path_slash);
		free(path_slash);
		return (FALSE);
	}
	update_current_dir(manager, path_slash);
	free(path_slash);
	return (TRUE);
}

t_bool	try_cd_arg(char *arg, t_manager *manager)
{
	char	*path_slash;

	path_slash = make_full_path(arg, manager->current_dir);
	if (chdir(path_slash) == SYS_FAILURE)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(arg);
		free(path_slash);
		return (FALSE);
	}
	update_current_dir(manager, path_slash);
	free(path_slash);
	return (TRUE);
}

int	do_cd(char **cmd_args, t_manager *manager)
{
	size_t	argc;

	argc = count_strs(cmd_args);
	if (argc > 2)
	{
		perror_arg2("cd", "too many arguments");
		return (1);
	}
	else if (argc == 1)
	{
		if (!try_cd_home(manager))
			return (1);
	}
	else
	{
		if (!try_cd_arg(cmd_args[1], manager))
			return (1);
	}
	return (0);
}
