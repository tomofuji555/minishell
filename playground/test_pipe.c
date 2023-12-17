# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <limits.h>

int test()
{
	int		pipefd[300000000];
	pid_t	pid;
	int		i;

	i = 0;
	// while(1)
	// {
	if (pipe(pipefd) == -1)
		return (1);
	else
		return (0);
		// else
		// { 
		// 	printf("%d,%d　成功！\n", i, i+1);
		// 	i += 2;
		// }
	// }
	
	// pid = fork();
	// if (pid == -1)
	// 	return (1);
	// else if (pid == 0)
	// {
	// 	printf("子プロセス\n");
	// }
	// else
	// 	printf("親プロセス\n");
	// 	return (0);
}

int	main()
{
	return (test());
}


// while() //今回はリダイレクト系トークンが来るまで
// {
// 	while(ヌル文字まで)
// 	{
// 		//値を入れていく
// 		i++;
// 	}	
// 	次のリストへ
// }

