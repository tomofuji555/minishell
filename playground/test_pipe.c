#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
//#include "../libft/libft.h"
#include "../execute.h"


static char	*make_path(char *cmd_name, char **envp)
{
	char	**path_lst;
	char	*cmd_path;
	size_t	i;

	path_lst = ft_split(getenv("PATH"), ':'); //xsplitに
	i = 0;
	while (path_lst[i] != NULL)
	{
		cmd_path = ft_strjoin(path_lst[i], ft_strjoin("/", cmd_name));
		if (access(cmd_path, F_OK) == EXIST)
			return (cmd_path);
		i++;
	}
	return (NULL);
}
void	_exec_cmd(char *argv)
{
	extern char **environ;
	char		**cmd_arg;
	char		*cmd_path;

	cmd_arg = ft_split(argv, ' ');
	cmd_path = make_path(cmd_arg[0], environ);
	execve(cmd_path, cmd_arg, environ);
}

	// close(pipefd[0]);
	// if (i != 1)
	// {
	// 	dup2(prev_fd, STDIN_FILENO);
	// 	close(prev_fd);
	// }
	// if (i != argc - 1)
	// 	dup2(pipefd[1], STDOUT_FILENO);
	// close(pipefd[1]);
void _change_stream(int i, int argc, int *pipefd, int prev_fd)
{
	close(pipefd[0]);
	if (argc == 2) //コマンドが1つのみ
	{
		close(pipefd[1]);
		return ;
	}
	if (i == 1) //最初のコマンド
		dup2(pipefd[1], STDOUT_FILENO);
	else if (i + 1 == argc) //最後のコマンド
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	else //途中のコマンド
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
		dup2(pipefd[1], STDOUT_FILENO);
	}
	close(pipefd[1]);
}

	// close(pipefd[1]);
	// if (i != 1)
	// 	close(*prev_fd);
	// if (i != argc - 1)
	// 	*prev_fd = pipefd[0];
	// else
	// 	close(pipefd[0]);
void _update_prev_fd(int i, int argc, int *pipefd, int *prev_fd)
{
	close(pipefd[1]);
	if (argc == 2) //コマンドが1つのみ
	{
		close(pipefd[0]);
		return ;
	}
	if (i == 1) //最初のコマンド
		*prev_fd = pipefd[0];
	else if (i + 1 == argc) //最後のコマンド
	{
		close(*prev_fd);
		close(pipefd[0]);
	}
	else //途中のコマンド
	{
		close(*prev_fd);
		*prev_fd = pipefd[0];
	}
}

int main(int argc, char **argv)
{
	int	i = 0;
	pid_t 	pid;
	int	pipefd[2];
	int	prev_fd = STDIN_FILENO;
	int status;

	while(i++ < argc - 1)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			_change_stream(i, argc, pipefd, prev_fd);
			_exec_cmd(argv[i]);
		}
		else
		{
			_update_prev_fd(i, argc, pipefd, &prev_fd);
		}
	}
	while(i-- > 1)
	{
		if (pid == wait(&status))
			; //printf("最終終了ステータス%d\n", WEXITSTATUS(status));
	}

}