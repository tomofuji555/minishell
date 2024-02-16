/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/19 16:46:17 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//#include <cstddef>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_bool
{
	FALSE	= 0,
	TRUE	= 1,
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

typedef struct	s_token
{
	enum e_token_kind	kind;
	char				*val;
	struct s_token		*next;
}	t_token;

enum e_redir_kind
{
	REDIR_IN_FILE		= 6,
	REDIR_HERE_DOC		= 7,
	REDIR_OUT_FILE		= 8,
	REDIR_APPEND_FILE	= 9,
};

typedef struct	s_init_arg_data
{
	t_token	*cmd_tokens;
	t_token	*infile_tokens;
	t_token	*outfile_tokens;
}	t_init_arg_data;

typedef struct	s_exec_arg_data
{
	char	**cmd_args;
	s_redir	*infile_paths;
	s_redir	*outfile_paths;
}	t_exec_arg_data;

typedef struct s_tree_node
{
	//t_token			*cmd_tokens;
	//t_token			*infile_tokens;
	//t_token			*outfile_tokens;
	t_init_arg_data	init_arg_data;
	t_exec_arg_data	exec_arg_data;
	struct s_tree_node	*prev;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
t_token	*lstlast(t_token *lst);
void	lst_add_back(t_token **lst, t_token *new);
ssize_t	split_to_token(t_token **head, char *line);
void	judge_token_type(t_token **node, char char1, char char2);
t_token	*make_new_token(char *start, ssize_t mv_count, int token_kind);
void	token_list(t_token **head, char *start, ssize_t count, int kind);
ssize_t	space_token(t_token **head, char *line);
void	free_lst_all(t_token **head);
ssize_t	text_token(t_token **head, char *line);
ssize_t	pipe_token(t_token **head, char *line);
ssize_t	quort_token(t_token **head, char *line);
ssize_t	output_token(t_token **head, char *line);
ssize_t	input_token(t_token **head, char *line);
ssize_t	quort_in_env(t_token **head, char *line);
ssize_t	env_token(t_token **head, char *line);
int		is_metachar(char c);
ssize_t	quort_error(void);
void	parse(t_token **head);
void	del_space_token(t_token **head);
t_token	*find_space_token(t_token *head);
t_token	*find_pre_space_token(t_token *head);
void	split_by_pipe(t_tree_node **tree, t_token **head, ssize_t count);
ssize_t	count_pipe(t_token *head);
t_token	*find_prev_last_pipe(t_token *head, ssize_t count);
t_token	*cmd_token(t_token **head, t_token *last_pipe, ssize_t count);
t_token	*find_last_pipe(t_token *head, ssize_t count);
t_tree_node	*prev_node(t_tree_node *prev_tree);
t_tree_node	*rs_tree_node(t_token **head, t_token *last_pipe, t_bool is_first, t_tree_node *prev_node);
t_tree_node	*init_rs_node(t_token **head, t_token *last_pipe, t_bool is_first, t_tree_node *prev_node);
t_token	*rs_append_node_and_add_null(t_token **head, t_token *last_pipe);
t_token	*cmd_of_rs(t_token **head, t_token *last_pipe, t_bool is_first);
t_token	*cmd_of_ls(t_token **head, t_token **last_pipe);
t_tree_node	*init_ls_node(t_token **head, t_token *last_pipe, t_tree_node *prev_node);
t_tree_node	*ls_tree_node(t_token **head, t_tree_node *prev_node);

#endif
