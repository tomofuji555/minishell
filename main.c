#include "execute.h"

int main()
{
	char *str = ft_strdup("$PWD $ $ABC $HOME$ZERO$HOME");
	printf("%s\n", str);
	printf("----------old----------\n");

	char *new_str = expand_env_in_str(str);
	printf("----------new----------\n");
	printf("sum %zd; %s;\n", ft_strlen(new_str) + 1,new_str);

	char *sumstr = "/Users/toshi/Desktop/42/42cursus/minishell $  /Users/toshi/Users/toshi";
	printf("sumstr %zd; %s;\n", ft_strlen(sumstr) + 1,sumstr);
}