#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
//#include "../execute.h"

int main(void)
{
	extern  char **environ;
	int i = 0;
	while(environ[i] != NULL)
	{
		if (strncmp(environ[i], "AAA", 3) == 0)
			free(environ[i]);
		i++;
	}
}

