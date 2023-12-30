/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:49 by toshi             #+#    #+#             */
/*   Updated: 2023/12/31 00:12:51 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q a.out");
// }


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
		if (*line != '\0') //改行だけじゃないとき
		{
			if (ft_strcmp(line, delim) == 0)
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
// 					filename = expansion_heredoc_ret_filepath("heredoc");
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
// }