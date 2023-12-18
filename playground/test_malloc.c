#include <stdlib.h>
#include <stdio.h>

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}

int main()
{
	int i = 0;
	char *str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
	{
		printf("error\n");
	}
	else
	{
		str[0] = '\0';
		printf("ok\n");
	}

}