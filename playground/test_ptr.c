#include "stdio.h"
#include "stdlib.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void a(char **str)
{
	(*str)++;
	printf("%zd\n", ft_strlen(*str));
}

int main()
{
	char *str = "ABCDEFGHIJKMNL";

	printf("before=%s;\n", str);
	a(&str);
	printf("after =%s;\n", str);

}
