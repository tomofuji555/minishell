/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/02/02 21:06:15 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
// #include "utils/utils.h"

#define	SYS_FAILURE	-1
#define	CHILD		0

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
	REDIR_APPEND_FILE
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

typedef struct s_exec_data
{
	char				**cmd_args;
	t_redir				*infile_paths;
	t_redir				*outfile_paths;
}	t_exec_data;

typedef struct s_tree_node
{
	t_init_data		init_data;
	t_exec_data		exec_data;
	struct s_tree_node	*prev;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_exec_handler
{
	t_tree_node		*cur_node;
	int				prev_pipe_in_fd;
}	t_exec_handler;


//~~~~utils start~~~~
//alloc_utils.c
void				*ft_xmalloc(size_t size);
void				*ft_xrealloc(void *ptr, size_t size);
void				*ft_xcalloc(size_t count, size_t size);
//bool_utils.c
t_bool				is_redir_token(enum e_token_kind kind);
t_bool				is_valuable_token(enum e_token_kind kind);
t_bool				is_ifs(char c);
t_bool				is_last_cmd(t_tree_node *cur_node);
t_bool				is_delim(char c);
t_bool				is_quote(char c);
t_bool				is_in_redir_tkn(enum e_token_kind kind);
t_bool				is_out_redir_tkn(enum e_token_kind kind);
//check_print_utils.c
void				print_to_last(char *begining, char *last);
void				tkn_print_lst(t_token *head);
void				tnode_print_lst(t_tree_node *tnode_ptr);
void				print_cmd_args(char **strs);
void				redir_print_lst(t_redir *head);
//env_utils.c
size_t				count_envname(char *dollar_ptr);
char				*ft_getenv(const char *target_str);
char				*search_env_val(char *dollar_ptr, size_t env_name_len);
//free_utils.c
void				free_tkn(t_token *tkn);
void				free_tkn_lst(t_token *head);
void				free_tnode(t_tree_node 	*tnode);
void				free_tnode_lst(t_tree_node *head);
//fujiwa_utils.c
void				lst_add_back(t_token **lst, t_token *new);
t_token				*make_new_token(char *start, ssize_t mv_count, int token_kind);
t_token				*lstlast(t_token *lst);
//redir_utils.c
void				change_stream_to_redir(t_redir *redir_head, int dest_fd);

//utils_1.c
void				perror_and_exit(char *err_title, int exit_status);
size_t				ft2_strlcat(char *dest, const char *src, size_t size);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_xstrdup(const char *s1);
char				*ft_xstrtrim(const char *s1, const char *set);
char				*ulltonbase(unsigned long long num, unsigned int base);
char				*ft_xsubstr(const char *s, unsigned int start, size_t len);
//~~~~utils end~~~~


//~~~~ tokenize start~~~~
//tokenize.c
t_token				*tokenize(char *line_ptr);
ssize_t				_count_untill_last(char *begining);
t_token				*make_new_tkn(char *begining, ssize_t count, enum e_token_kind kind);

//tokenize_utils1.c
ssize_t				count_untill_text_last(char *begining);
ssize_t				count_untill_ifs_last(char *begining);
ssize_t				count_untill_redir_last(char *begining);
ssize_t				count_untill_quote_last(char *begining);
ssize_t				count_untill_dollar_last(char *begining);
//tokenize_utils2.c
enum e_token_kind	_save_redir_tkn_kind(char *begining);
enum e_token_kind	_save_env_or_text_kind(char *begining);
enum e_token_kind	save_tkn_kind(char *begining);
t_token				*find_last_tkn(t_token *head);
void				add_last_tkn(t_token **head, t_token *new);
//tkn_utils.c
t_token				*save_prev_tkn(t_token *head, t_token *target);
t_token				*find_last_valuable_tkn(t_token *tkn_ptr);
char				*substr_from_tkn(t_token *begining, t_token *last);
//~~~~ tokenize end~~~~

//~~~~ parse start~~~~
// // paese.c
t_tree_node			*parse(t_token *tkn_ptr);
static t_tree_node	*_make_new_tnode(t_token *tkn_begining, t_token *tkn_ptr);
static void			_fill_null_last_tkn_of_tnode(t_tree_node *tnode_ptr);
static void			_add_last_tnode(t_tree_node **head, t_tree_node *new);
static t_tree_node	*_find_last_tnode(t_tree_node *head);
// parse_utils1.c
void				push_to_redir_tkns(t_tree_node *tnode_ptr);
t_token				*separate_and_make_redir_tkns_lst(t_token *ptr, t_bool (*is_func)(enum e_token_kind));
static void			_add_redir_tkns_last(t_token **head, t_token *prev_of_first, t_token *last);
t_token				*save_redir_tkn_last(t_token *tkn_ptr);
//~~~~parse end~~~~


//~~~~expansion start~~~~
// expansion.c
void	expansion(t_tree_node *ptr);
void	expansion_tkns(t_token **tkn_head);
//expand_env.c
void	expand_env_of_tkn(t_token **head, t_token *env_tkn, t_token *prev_of_env_tkn);
//expand_env_in_dquote.c
char *expand_env_in_dquote(char *str);
//make_cmd_args.c
char **make_cmd_args(t_token *tkn_head);
//make_redir_list.c
t_redir	*redir_make_lst(t_token *tkn_ptr);
#endif 