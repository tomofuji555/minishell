/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/30 23:56:07 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

enum	e_pipefd_direct
{
	IN	= 0,
	OUT	= 1
};

typedef enum e_bool
{
	FALSE	= 0,
	TRUE	= 1
}	t_bool;

enum e_token_kind
{
	TKN_SPACE		= 0,
	TKN_TEXT		= 1,
	TKN_S_QUOTE		= 2,
	TKN_D_QUOTE		= 3,
	TKN_ENV			= 4,
	TKN_PIPE		= 5,
	TKN_IN_FILE		= 6,
	TKN_HERE_DOC	= 7,
	TKN_OUT_FILE	= 8,
	TKN_APPEND_FILE = 9,
};

enum e_redir_kind
{
	REDIR_IN_FILE		= 6,
	REDIR_HERE_DOC		= 7,
	REDIR_OUT_FILE		= 8,
	REDIR_APPEND_FILE	= 9,
};

typedef struct s_token
{
	enum e_token_kind	kind;
	char				*val;
	struct s_token		*next;
}	t_token;

typedef struct s_redir
{
	enum e_redir_kind	kind;
	char				*val;
	struct s_redir		*next;
}	t_redir;

typedef struct s_init_arg_data
{
	t_token				*cmd_tokens;
	t_token				*infile_tokens;
	t_token				*outfile_tokens;
}	t_init_arg_data;

typedef struct s_exec_arg_data
{
	char				**cmd_args;
	t_redir				*infile_paths;
	t_redir				*outfile_paths;
}	t_exec_arg_data;

typedef struct s_tree_node
{
	t_init_arg_data		init_arg_data;
	t_exec_arg_data		exec_arg_data;
	struct s_tree_node	*prev;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_exec_handler
{
	t_tree_node		*cur_node;
	int				prev_pipe_in_fd;
}	t_exec_handler;

char	*expand_env_in_str(char *str);
char	*ft_getenv(const char *name);
int		is_equal_str_untill_delim(const char *s1, const char *s2, const char delim);
void	*ft_xrealloc(void *ptr, size_t size);
void 	*ft_xmalloc(size_t size);
void perror_and_exit(char *err_title, int exit_status);
int		ft_strcmp(const char *s1, const char *s2);
int is_valuable_token(enum e_token_kind kind);

#endif