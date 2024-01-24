#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../execute.h"

int main()
{
	size_t i = 10;
	int fd = open("./a", O_RDWR , S_IRWXU);
	// int fd = open(NULL, O_RDWR , S_IRWXU);
	if (fd == -1)
		perror("fd");
	if (unlink("./a") == -1)
		perror("unlink");
	char *buf = (char *)malloc(sizeof(char) * (i + 1));
	if (read(fd, buf, i) == -1)
		perror("read");
	buf[i] = '\0';
	printf("%s\n", buf);
}