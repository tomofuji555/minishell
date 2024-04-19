/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syswrap2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:45:54 by toshi             #+#    #+#             */
/*   Updated: 2024/04/19 20:34:42 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	ft_xclose(int fd)
{
	if (close(fd) == SYS_FAILURE)
		perror_and_exit("close", 1);
}

void	ft_xpipe(int *pipefd)
{
	if(pipe(pipefd) == SYS_FAILURE)
		perror_and_exit("pipe", 1);
}

pid_t	ft_xfork(void)
{
	pid_t pid;

	pid = fork();
	if (pid == SYS_FAILURE)
		perror_and_exit("fork", 1);
	return (pid);
}

//accessでパスが保証されているコマンドが引数で入ってきている
//execがエラーを出した時は実行許可がないパターンしか想定していない
void	ft_xexecve(char *cmd_path, char **cmd_args, t_env *env_list)
{
	char **envp;

	envp = make_envp(env_list);
	if (execve(cmd_path, cmd_args, envp) == SYS_FAILURE)
		perror_and_exit(cmd_args[0], 126);
}
