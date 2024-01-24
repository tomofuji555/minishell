#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../execute.h"

int fork_exec(char *path, char *arg[], char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
	{
		execve(path, arg, NULL);
		// // exit(199);
		// while(1);
	}
	else
	{
		wait(&status);
		printf("親プロセスは終了ステータス%dで終了しました\n", WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}

int main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	char	*path = "/bin/qq";
	char	*arg[] = {"ls", "-a", NULL};
	int		status;
	int val;

	pid = fork();
	if (!pid)
	{
		// // execve(path, arg, NULL);
		// // exit(199);
		// while(1);
		val = fork_exec(path, arg, NULL);
		
		printf("--子プロセスは終了ステータス%dで終了しました\n", val);
	}
	else
	{
		wait(&status);
		// printf("子プロセスは終了ステータス%dで終了しました\n", WEXITSTATUS(status));
		// printf("子プロセスはシグナル番号%dで終了しました\n", WTERMSIG(status));
	}
}