/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:11:11 by tozeki            #+#    #+#             */
/*   Updated: 2024/02/04 20:11:41 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//static char	*get_val_envvar(char **envp, char *envvar)
//{
//	size_t	i;

//	i = 0;
//	while (envp[i] != NULL)
//	{
//		if (ft_strncmp(envp[i], envvar, ft_strlen(envvar)) == 0)
//			return (ft_strchr(envp[i], '=') + (sizeof(char) * 1));
//		i++;
//	}
//	return (NULL);
//}

//static char	*append_str(char *dest, char *src, size_t count)
//{
//	size_t	len;
//	char	*buf;

//	if (dest == NULL)
//		return (NULL);
//	if (src == NULL || count <= 0)
//		return (dest);
//	len = ft_strlen(dest) + count + 1;
//	buf = (char *)ft_calloc(len, sizeof(char));
//	if (buf == NULL)
//	{
//		free(dest);
//		return (NULL);
//	}
//	ft_strlcat(buf, dest, len);
//	ft_strlcat(buf, src, len);
//	free(dest);
//	return (buf);
//}

//static t_bool	is_set_access_path(char *cmd, char *path, char **ptr_cmd_path)
//{
//	*ptr_cmd_path = append_str(ft_strjoin(path, "/"), cmd, ft_strlen(cmd));
//	if (*ptr_cmd_path == NULL)
//		return (perror_ret_false("malloc"));
//	if (access(*ptr_cmd_path, X_OK) == 0)
//		return (TRUE);
//	else
//		return (FALSE);
//}

static char	*get_absolute_path(char *cmd_name, char **environ)
{
	char	**path_lst;
	char	*cmd_path;
	size_t	i;

	path_lst = ft_xsplit(ft_getenv("PATH"), ':'); //xsplitに
	i = 0;
	while (path_lst[i] != NULL)
	{
		cmd_path = ft_xstrjoin(path_lst[i], ft_xstrjoin("/", cmd_name));
		if (access(cmd_path, X_OK) == 0)
		{
			free_all(path_lst);
			return (cmd_path);
		}
		else
			free(cmd_path);
		i++;
	}
	free_all(path_lst);
	return (NULL);
}

t_bool	exec_cmd(char **cmd_args, char **envp)
{
	char		*cmd_path;

	if (ft_strchr(cmd_args[0], '/') != NULL)
		;//絶対パス(スラッシュあり)か、今の階層にあるファイルなら(accessで確認)相対パスを探す必要はない
	cmd_path = get_absolute_path(cmd_args[0], envp);
	if (cmd_path == NULL)
	{
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (FALSE);
	}
	execve(cmd_path, cmd_args, envp); //ft_xexceve
	return (TRUE);
}
