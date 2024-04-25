/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/04/25 02:30:21 by toshi            ###   ########.fr       */
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

# define SYS_FAILURE	-1
# define CHILD			0
# define EXIST			0
# define NOT_EXIST		-1
# define DEFAULT		0
# define AMBIGUOUS		NULL


int	g_signal_flag;

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
	TKN_HEREDOC,
	TKN_OUT_FILE,
	TKN_APPEND_FILE,
};

enum e_redir_kind
{
	REDIR_IN_FILE,
	REDIR_HEREDOC,
	REDIR_HEREDOC_NO_EXPAND,
	REDIR_OUT_FILE,
	REDIR_APPEND_FILE,
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
	t_init_data			init_data;
	t_adv_data			adv_data;
	struct s_tree_node	*prev;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_env
{
	char				*key;
	char				*val;
	struct s_env		*next;
}	t_env;

typedef struct s_manager
{
	t_env	*env_list;
	char	*current_dir;
	char	*exit_status;
	int		heredoc_line;
}	t_manager;

t_manager	initialize(void);
void		finalize(t_manager *manager);

#endif
