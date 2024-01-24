/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:49 by toshi             #+#    #+#             */
/*   Updated: 2024/01/14 22:42:06 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execute.h"

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q a.out");
// }


//ULLMAX通り以上のファイルを作成されるとエラー
char	*create_tmpfile_path(void)
{
	unsigned long long num;
	char *path;

	num = 0;
	while (num < ULLONG_MAX)
	{
		path = ft_strjoin("/tmp/", ulltonbase(num++, 16));
		if (path == NULL)
			perror_and_exit("malloc", 1);
		if (access(path, F_OK) == SYS_FAILURE)
			return (path);
		free (path);
	}
	ft_putendl_fd("file_error: unexpected number of files", STDERR_FILENO);
	exit(1);
}

//kindがREDIR_HEREDOC_NO_EXPANDでなければEXPAND
//putし、そのlineをfree
void put_fd_and_free_line(int fd, char *line, enum e_redir_kind kind)
{
	if (kind == REDIR_HEREDOC)
		line = expand_env_in_dquote(line);
	ft_putendl_fd(line, fd);
	free(line);
}

//heredocで書き込んだファイルのpathを返す
//delimのfreeは無し
char	*run_heredoc(char *delim, enum e_redir_kind kind)
{
	char	*line;
	char	*path;
	int		fd;

	path = ft_strdup("aaa");
	fd = open(path, O_WRONLY | O_CREAT, S_IRWXU);
	if (fd == SYS_FAILURE)
		;//検討
	while(1)
	{
		line = readline("> ");
		if (line == NULL)
			;//error_and_exit
		if (ft_strcmp(line, delim) == 0)
			break;
		else
			put_and_free_line(fd, line, kind);
	}
	free(line);
	close(fd);
	return (path);
}

// int main()
// {
// 	char *line;
// 	char *filename = NULL;

// 	while(1)
// 	{
// 		line = readline("minishell $ ");
// 		if (line == NULL)
// 			printf("error\n");
// 		else
// 		{
// 			if(*line != '\0')
// 			{
// 				add_history(line);
// 				if (ft_strcmp(line, "heredoc") == 0)
// 					filename = run_heredoc("heredoc");
// 				if (ft_strcmp(line, "end") == 0)
// 				{
// 					free(line);
// 					break;
// 				}
// 			}
// 			free(line);
			
// 			// printf("line=\"%s\"", line);
// 			// printf("\n");
// 			// free(line);
// 		}
// 	}
// 	printf("file名 %s\n", filename);
// 	free(filename);
// }