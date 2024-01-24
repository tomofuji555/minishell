#include <stdio.h>
#include <stdlib.h>

char *get_quote_last(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	while(*ptr && *ptr != *begining)
		ptr++;
	if (*ptr == '\0')
		return (NULL);
	return (ptr);
}

int main()
{
	char *str = "\"ngla\"";

	printf("==%s\n", get_quote_last(str));
	// printf ("%s\n", getenv("?")); //エラー
}