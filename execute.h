/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/23 17:07:14 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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

// typedef struct s_tree_node
// {
// 	t_token			*cmd_tokens;
// 	t_token			*infile_tokens;
// 	t_token			*outfile_tokens;
// 	char			**cmd_args;
// 	t_redir			*infile_paths;
// 	t_redir			*outfile_paths;
// 	struct s_node	*prev;
// 	struct s_node	*left;
// 	struct s_node	*right;
// }	t_tree_node;

// typedef struct s_exec_handler
// {
// 	t_tree_node		*cur_node;
// 	char			**strs;				//execまで使わない
// 	t_redir			*infile_paths;		//execまで使わない
// 	t_redir			*outfile_paths;		//execまで使わない
// 	int				prev_pipe_in_fd;
// }	t_exec_handler;


t_redir	*make_redir_list(t_token *tkn_ptr);
void	print_token_list(t_token *head);
t_token *make_token_node(char *str, enum e_token_kind kind);
t_token *find_last_node(t_token *head);
void add_node_last(t_token **head, t_token *new);
t_token	*test_make_token_list(char *strs[], enum e_token_kind kinds[]);


t_redir	*make_redir_list(t_token *tkn_ptr);
int	is_redir_token(enum e_token_kind kind);
size_t	strlen_of_list_untill_last(t_token *begining, t_token *last);
size_t	strlcpy_from_list(char *dest, t_token *src, size_t len);
enum e_redir_kind	convert_redir_kind(enum e_token_kind token_kind);
t_redir	*make_redir_node(t_token *begining, t_token *last);
t_redir	*find_last_redir_node(t_redir *head);
void	add_redir_node_last(t_redir **head_node, t_redir *new_node);


#endif