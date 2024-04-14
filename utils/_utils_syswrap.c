/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_syswrap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:14:55 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/14 12:40:09 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void *ft_xmalloc(size_t size)
{
	void *ret;

	if (size == 0)
		return (NULL);
	ret = (void *)malloc(size);
	if (ret == NULL)
		perror_and_exit("malloc", 1);
	return (ret);
}

void *ft_xrealloc(void *ptr, size_t size)
{
	if (ptr != NULL)
		free(ptr);
	if (size == 0)
		return (NULL);
	return (ft_xmalloc(size));
}

void *ft_xcalloc(size_t count, size_t size)
{
	void *ret;

	if (count == 0 || size == 0 || size > SIZE_MAX / count)
		return (NULL);
	ret = (void *)malloc(size * count);
	if (ret == NULL)
		perror_and_exit("malloc", 1);
	ft_memset(ret, '\0', count * size);
	return (ret);
}

int ft_xdup2(int copied_fd, int dest_fd)
{
	if (dup2(copied_fd, dest_fd) == SYS_FAILURE)
		perror_and_exit("dup2", 1);
	return (dest_fd);
}

int ft_xdup(int copied_fd)
{
	int dest_fd;

	dest_fd = dup(copied_fd);
	if (dest_fd == SYS_FAILURE)
		perror_and_exit("dup", 1);
	return (dest_fd);
}

void ft_xclose(int fd)
{
	if (close(fd) == SYS_FAILURE)
		perror_and_exit("close", 1);
}

void ft_xpipe(int *pipefd)
{
	if(pipe(pipefd) == SYS_FAILURE)
		perror_and_exit("pipe", 1);
}

pid_t ft_xfork(void)
{
	pid_t pid;

	pid = fork();
	if (pid == SYS_FAILURE)
		perror_and_exit("fork", 1);
	return (pid);
}

int ft_xunlink(char *pathname)
{
	if (unlink(pathname) == SYS_FAILURE)
		perror_and_exit("unlink", 1);
	return (0);
}

static size_t count_envvar(t_env *env_list)
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

static char **make_envp(t_env *env_list)
{
	char	**envp;
	t_env	*ptr;
	size_t	i;

	envp = (char **)ft_xmalloc(sizeof(char *) * (count_envvar(env_list) + 1));
	i = 0;
	ptr = env_list;
	while (ptr != NULL)
	{
		envp[i++] = join_and_free_str2(env_list->key, ft_xstrjoin("=", env_list->val));
		ptr = ptr->next;
	}
	envp[i] = NULL;
	return (envp);
}

//accessでパスが保証されているコマンドが引数で入ってきている
//execがエラーを出した時は実行許可がないパターンしか想定していない
void ft_xexecve(char *cmd_path, char **cmd_args, t_env *env_list)
{
	char **envp;

	envp = make_envp(env_list);
	if (execve(cmd_path, cmd_args, envp) == SYS_FAILURE)
		perror_and_exit(cmd_args[0], 126);
}