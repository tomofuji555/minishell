#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

int main()
{
	errno = 0;
	// size_t i = 4294967295;
	char *str = (char *)malloc(sizeof(char) * (9999999999999999999 + 1));
	if (str == NULL)
	{
		perror("lalala");
		// strerror(errno);
		printf("%s\n", strerror(errno));
	}
	else
	{
		str[0] = '\0';
		printf("ok\n");
	}

}