
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd = STDOUT_FILENO;
	int fd2 = dup(STDOUT_FILENO); 
	printf("fd2 = %d  %d\n", fd2, STDOUT_FILENO);
	if (dup2(fd2, STDOUT_FILENO) == -1)
		printf("エラー\n");
	
}