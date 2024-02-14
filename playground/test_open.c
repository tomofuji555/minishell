#include "../execute.h"
#include <string.h>
#include <errno.h>

void read_print(int fd, int i)
{
	char *buf = (char *)malloc(sizeof(char) * (i + 1));
	if (read(fd, buf, i) == -1)
	{
		//perror("123");
	}
	buf[i] = '\0';
	printf("%s\n", buf);
}

	//fd = open(node->val, O_RDONLY);
	//fd = open(node->val, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	//fd = open(node->val, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
int main()
{
	errno = 0;
	//int fd = open("  a  b  v  ", O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	int fd = open("  a  b  v  ", O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	if (fd == -1)
	{
		perror("123");
		//strerror(errno);
	}
	//read_print(fd, 10);
	write(fd, "aaaa\n", 5);
}