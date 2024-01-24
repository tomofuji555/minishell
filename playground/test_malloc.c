#include <stdlib.h>
#include <stdio.h>

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}

int main()
{
	// size_t i = 4294967295;
	char *str = (char *)malloc(sizeof(char) * (999999999999999 + 1));
	if (str == NULL)
	{
		perror("");
		// printf("error\n");
	}
	else
	{
		str[0] = '\0';
		printf("ok\n");
	}

}