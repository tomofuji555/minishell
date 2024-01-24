#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../execute.h"


static char	*get_val_envvar(char **envp, char *envvar)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], envvar, ft_strlen(envvar)) == 0)
			return (ft_strchr(envp[i], '=') + (sizeof(char) * 1));
		i++;
	}
	return (NULL);
}

static char	*append_str(char *dest, char *src, size_t count)
{
	size_t	len;
	char	*buf;

	if (dest == NULL)
		return (NULL);
	if (src == NULL || count <= 0)
		return (dest);
	len = ft_strlen(dest) + count + 1;
	buf = (char *)ft_calloc(len, sizeof(char));
	if (buf == NULL)
	{
		free(dest);
		return (NULL);
	}
	ft_strlcat(buf, dest, len);
	ft_strlcat(buf, src, len);
	free(dest);
	return (buf);
}

static t_bool	is_set_access_path(char *cmd, char *path, char **ptr_cmd_path)
{
	*ptr_cmd_path = append_str(ft_strjoin(path, "/"), cmd, ft_strlen(cmd));
	if (access(*ptr_cmd_path, X_OK) == 0)
		return (TRUE);
	else
		return (FALSE);
}

static char	*get_absolute_path(char **cmd_opts, char **environ)
{
	char	**path_list;
	char	*cmd_path;
	size_t	i;

	path_list = ft_split(get_val_envvar(environ, "PATH"), ':');
	if (path_list == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (path_list[i] != NULL)
	{
		if (is_set_access_path(cmd_opts[0], path_list[i], &(cmd_path)) == TRUE)
		{
			return (cmd_path);
		}
		else
			free(cmd_path);
		i++;
	}
	return (NULL);
}

t_bool	exec_cmd(char **cmd_opts)
{
	char		*cmd_path;
	extern char	**environ;

	cmd_path = get_absolute_path(cmd_opts, environ);
	if (cmd_path == NULL)
	{
		perror("not found filepath");
		exit(127);
	}
	execve(cmd_path, cmd_opts, environ);
	return (TRUE);
}

static t_bool	set_cmd_opts(char ***cmd_opts, char *arg_str)
{
	*cmd_opts = ft_split(arg_str, ' ');
	return (TRUE);
}

void _exec_cmd(char *argv)
{
	char **arg_list;
	set_cmd_opts(&arg_list, argv);
	exec_cmd(arg_list);
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
			printf("最終終了ステータス%d\n", WEXITSTATUS(status));
	}

}