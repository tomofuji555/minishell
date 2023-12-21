#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


__attribute__((destructor))
static void destructor() {
   system("leaks -q a.out");
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (i == n)
		return (0);
	else
		return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

char	*expansion_heredoc_ret_filepath(char *delim)
{
	char	*line;
	char	*path = "./aaa.txt";
	int		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

	while(1)
	{
		line = readline("> ");
		if (line == NULL)
			printf("error\n");
		if (*line != '\0')
		{
			if (ft_strncmp(line, "heredoc", ft_strlen(line)) == 0)
			{
				free(line);
				break;
			}
			else
			{
				write(fd, line, ft_strlen(line));
			}
		}
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (path);
}

int main()
{
	char *line;
	char *filename;

	while(1)
	{
		line = readline("minishell $ ");
		if (line == NULL)
			printf("error\n");
		else
		{
			if(*line != '\0')
			{
				add_history(line);
				if (ft_strncmp(line, "heredoc", ft_strlen(line)) == 0)
					filename = expansion_heredoc_ret_filepath("heredoc");
				if (ft_strncmp(line, "end", ft_strlen(line)) == 0)
				{
					free(line);
					break;
				}
			}
			free(line);
			
			// printf("line=\"%s\"", line);
			// printf("\n");
			// free(line);
		}
	}
	printf("file名 %s\n", filename);
}