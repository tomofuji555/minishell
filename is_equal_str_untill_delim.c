#include "execute.h"

int	is_equal_str_untill_delim(const char *s1, const char *s2, const char delim) //本当はbefore
{
	size_t	i;
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] != delim && s2[i] != delim && s1[i] == s2[i])
		i++;
	printf("s1=%c; s2=%c\n", s1[i], s2[i]);
	if (s1[i] == delim && s2[i] == delim)
		return (TRUE);
	else
		return (FALSE);

	// size_t offset = (size_t)(ft_strchr(s1, delim) - s1);
	// char *new_str = ft_substr(s1, 0, offset - 1);
	// if (ft_strncmp(new_str, s2, ft_strlen(new_str)) == 0)
	// {
	// 	free(new_str);
	// 	return (TRUE);
	// }
	// else
	// {
	// 	free(new_str);
	// 	return (FALSE);
	// }
}

// int main()
// {
// 	//-----------------------------
// 	char *s1 = "ABC";
// 	char *s2 = "ABC";
// 	if (is_equal_str_untill_delim(s1, s2, ';') == TRUE)
// 		printf("ok\n");
// 	else
// 		printf("ko\n");
// 	//-----------------------------
// 	char *s3 = "ABCD;";
// 	char *s4 = "ABC;E";
// 	if (is_equal_str_untill_delim(s3, s4, ';') == TRUE)
// 		printf("ok\n");
// 	else
// 		printf("ko\n");
// 	//-----------------------------
// 	char *s5 = "ABC;E";
// 	char *s6 = "ABCD;";
// 	if (is_equal_str_untill_delim(s5, s6, ';') == TRUE)
// 		printf("ok\n");
// 	else
// 		printf("ko\n");
// 	//-----------------------------
// 	char *s7 = "ABC;E";
// 	char *s8 = "ABC;D";
// 	if (is_equal_str_untill_delim(s7, s8, ';') == TRUE)
// 		printf("ok\n");
// 	else
// 		printf("ko\n");
// }