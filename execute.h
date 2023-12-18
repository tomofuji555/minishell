/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/18 18:03:00 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>

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
	TKN_HEAD		= -1,
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

typedef struct s_tree_node
{
	t_token			*cmd_tokens;
	t_token			*infile_tokens;
	t_token			*outfile_tokens;
	int				last_cmd_flag;
	struct s_node	*prev;
	struct s_node	*left;
	struct s_node	*right;
}	t_tree_node;

typedef struct s_redir
{
	enum e_redir_kind	kind;
	char				*val;
	struct s_token		*next;
}	t_redir;

typedef struct s_exec_handler
{
	t_tree_node		*cur_node;
	char			**strs;				//execまで使わない
	t_redir			*infile_paths;		//execまで使わない
	t_redir			*outfile_paths;		//execまで使わない
	int				prev_pipe_in_fd;
}	t_exec_handler;

#endif
