/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:49 by toshi             #+#    #+#             */
/*   Updated: 2024/02/24 18:04:14 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execute.h"
//ULLMAX通り以上のファイルを作成されるとエラー
char	*create_tmpfile_path(void)
{
	unsigned long long num;
	char *path;

	num = 0;
	while (num < ULLONG_MAX)
	{
		path = ft_xstrjoin("/tmp/", ulltonbase(num++, 16));
		if (access(path, F_OK) == NOT_EXIST)
			return (path);
		free (path);
	}
	ft_putendl_fd("file_error: unexpected number of files", STDERR_FILENO); //perror_and_exitに置き換え
	exit(1);
}

//kindがREDIR_HEREDOC_NO_EXPANDでなければEXPAND
//putし、そのlineをfree
void output_fd_and_free_line(int fd, char *line, enum e_redir_kind heredoc_kind)
{
	if (heredoc_kind == REDIR_HEREDOC)
		line = expand_env_in_dquote(line);
	ft_putendl_fd(line, fd);
	free(line);
}

//heredocで書き込んだファイルのpathを返す
//delimのfreeは無し
char	*run_heredoc(char *delim, enum e_redir_kind heredoc_kind)
{
	char	*line;
	char	*path;
	int		fd;

	path = create_tmpfile_path();
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
			output_fd_and_free_line(fd, line, heredoc_kind);
	}
	free(line);
	ft_xclose(fd);
	return (path);
}



void	try_heredoc(t_tree_node *tnode_head)
{
	t_tree_node *ptr;
	t_redir	*rdir_ptr;

	ptr = tnode_head;
	while (ptr != NULL)
	{
		rdir_ptr = ptr->exec_data.infile_paths;
		while (rdir_ptr != NULL)
		{
			if (rdir_ptr->kind == REDIR_HEREDOC || \
				rdir_ptr->kind == REDIR_HEREDOC_NO_EXPAND)
				rdir_ptr->val = run_heredoc(rdir_ptr->val, rdir_ptr->kind);
			rdir_ptr = rdir_ptr->next;
		}
		ptr = ptr->right;
	}
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