/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/09 15:52:40 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>

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
	struct s_node	*prev;
	struct s_node	*left;
	struct s_node	*right;
}	t_tree_node;

typedef struct s_exec_handler
{
	char	**strs;
	char	*infile_path;
	char 	*outfile_path;
}	t_exec_handler;

#endif
