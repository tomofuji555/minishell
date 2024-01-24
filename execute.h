/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/01/23 00:20:10 by toshi            ###   ########.fr       */
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
void				tkn_free(t_token *tkn);
void				tkn_free_lst(t_token *head);
void				tnode_free(t_tree_node 	*tnode);
void				tnode_free_lst(t_tree_node *head);
//fujiwa_utils.c
void				lst_add_back(t_token **lst, t_token *new);
t_token				*make_new_token(char *start, ssize_t mv_count, int token_kind);
t_token				*lstlast(t_token *lst);
//redir_utils.c
void				change_stream_to_redir(t_redir *redir_head, int dest_fd);
//tkn_utils.c
t_token *save_prev_tkn(t_token *head, t_token *target);
t_token				*tkn_find_valuable_last(t_token *tkn_ptr);
t_token				*tkn_find_last(t_token *head);
void				tkn_add_last(t_token **head, t_token *new);
char				*substr_from_tkn(t_token *begining, t_token *last);
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
t_token 			*tkn_make_new(char *begining, char *last);
enum e_token_kind	tkn_save_kind(char *begining);
char				*save_last_chr(char *begining);
ssize_t count_last(char *begining);
//tokenize_utils1.c
char				*save_text_last(char *begining);
char				*save_space_last(char *begining);
char				*save_redir_last(char *begining);
char				*save_quote_last(char *begining);
char				*save_env_last(char *begining);
//tokenize_utils2.c
enum e_token_kind	save_redir_tkn_kind(char *begining);
enum e_token_kind	save_env_or_text_kind(char *begining);
char 				*tkn_substr(char *begining, char *last);
char 				*tkn_substr_into_quote(char *begining, char *last);
//tokenize_utils3.c
ssize_t				count_text_last(char *begining);
ssize_t				count_ifs_last(char *begining);
ssize_t				count_redir_last(char *begining);
ssize_t				count_quote_last(char *begining);
ssize_t				count_dollar_last(char *begining);
//~~~~ tokenize end~~~~

//~~~~ parse start~~~~
// // paese.c
t_tree_node			*parse(t_token *tkn_head);
void				push_all_redir_tkns(t_tree_node *tnode_ptr);
t_tree_node			*make_tree_lst(t_token *tkn_ptr);
// parse_utils1.c
t_token *push_redir_tkns(t_token *ptr, t_bool (*is_func)(enum e_token_kind));
t_token *save_last_for_redir_tkns(t_token *tkn_ptr);
// parse_utils2.c
void				tnode_add_last_right(t_tree_node **head, t_tree_node *new);
t_tree_node			*tnode_find_last_right(t_tree_node *head);
//~~~~parse end~~~~


//~~~~expansion start~~~~
// expansion.c
void	expansion(t_tree_node *ptr);
void	expansion_tkns(t_token **tkn_head);
//expand_env.c
t_token *expand_env(t_token *env_tkn);
//expand_env_in_dquote.c
char *expand_env_in_dquote(char *str);
//make_cmd_args.c
char **make_cmd_args(t_token *tkn_head);
//make_redir_list.c
t_redir	*redir_make_list(t_token *tkn_ptr);
#endif 