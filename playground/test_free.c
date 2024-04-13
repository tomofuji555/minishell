#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 __attribute__((destructor))
static void destructor() {
   system("leaks -q a.out");
}

void ft_xfree(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

int main()
{
	char *str = strdup("abcdefg");
	printf("%s\n", str);
	// free(str);
	// str = NULL;
	ft_xfree((void **)&str);
	printf("%s\n", str);
}
