/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/04/13 14:35:42 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef enum e_bool
{
	FALSE	= 0,
	TRUE	= 1
}	t_bool;

enum e_token_kind
{
	TKN_SPACE			= 0,
	TKN_TEXT			= 1,
	TKN_S_QUOTE			= 2,
	TKN_D_QUOTE			= 3,
	TKN_ENV				= 4,
	TKN_PIPE			= 5,
	TKN_IN_FILE			= 6,
	TKN_HEREDOC		= 7,
	TKN_OUT_FILE		= 8,
	TKN_APPEND_FILE		= 9,
};

typedef struct s_token
{
	enum e_token_kind	kind;
	char				*val;
	struct s_token		*next;
}	t_token;

enum e_redir_kind
{
	REDIR_IN_FILE,
	REDIR_HEREDOC,
	REDIR_HEREDOC_NO_EXPAND,
	REDIR_OUT_FILE,
	REDIR_APPEND_FILE,
};

typedef struct s_redir
{
	enum e_redir_kind	kind;
	char				*val;
	struct s_redir		*next;
}	t_redir;

typedef struct s_init_data
{
	t_token				*cmd_tokens;
	t_token				*infile_tokens;
	t_token				*outfile_tokens;
}	t_init_data;

typedef struct s_adv_data
{
	char				**cmd_args;
	t_redir				*infile_paths;
	t_redir				*outfile_paths;
}	t_adv_data;

typedef struct s_tree_node
{
	t_init_data		init_data;
	t_adv_data		adv_data;
	struct s_tree_node	*prev;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

void print_tkn_list(t_token *ptr);
void	print_init_data(t_tree_node *ptr);
void	wc(char *str);

#endif
