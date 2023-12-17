/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/16 14:59:01 by toshi            ###   ########.fr       */
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
	TKN_SPACE,
	TKN_TEXT,
	TKN_S_QUOTE,
	TKN_D_QUOTE,
	TKN_ENV,
	TKN_PIPE,
	TKN_IN_FILE,
	TKN_HERE_DOC,
	TKN_OUT_FILE,
	TKN_APPEND_FILE,
};

enum e_redir_kind
{
	REDIR_IN_FILE,
	REDIR_HERE_DOC,
	REDIR_OUT_FILE,
	REDIR_APPEND_FILE,
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
