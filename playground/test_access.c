#include "../execute.h"
#include <string.h>
#include <errno.h>

int main()
{
	errno = 0;
	int fd = open("  a  b  v  ", O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	if (access("/usr/local/bin/", F_OK) == -1)
	{
		perror("123");
		//strerror(errno);
	}
	printf("bagbkagka\n");
}