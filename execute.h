/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/02/24 16:53:03 by tozeki           ###   ########.fr       */
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
#include "stdbool.h"
// #include "utils/utils.h"

#define	SYS_FAILURE	-1
#define	CHILD		0
#define EXIST		0
#define NOT_EXIST	-1
#define DEFAULT		0
#define AMBIGUOUS	NULL

enum	e_pipefd_direct
{
	R	= 0,
	W	= 1
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
	AMBIGUOUS_REDIR,
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

typedef struct s_manager
{
	char	**envp;
	int		exit_status;
	int		prev_output_fd;
	size_t	fork_count;
	pid_t	last_pid;
	bool	last_cmd_flag;
	bool	first_cmd_flag;
}	t_manager;

//~~~~utils start~~~~
//bool_utils.c
t_bool	 			is_delim(char c);
t_bool				is_ifs(char c);
t_bool				is_quote(char c);
t_bool				is_valuable_tkn(enum e_token_kind kind);
t_bool				is_redir_tkn(enum e_token_kind kind);
t_bool				is_in_redir_tkn(enum e_token_kind kind);
t_bool				is_out_redir_tkn(enum e_token_kind kind);
t_bool				is_last_cmd(t_tree_node *ptr);
t_bool				is_first_cmd(t_tree_node *ptr);
t_bool				is_cmd_node(t_tree_node *ptr);
t_bool	is_absolute_path_cmd(char *first_cmd_arg);
//env_utils.c
size_t				count_envname(char *dollar_ptr);
char				*ft_getenv(const char *target_str);
char				*search_env_val(char *dollar_ptr, size_t env_name_len);
//free_utils.c
void				free_multi_strs(char **strs);
void				free_tkn(t_token *tkn);
void				free_tkn_lst(t_token *head);
void				free_tnode(t_tree_node 	*tnode);
void				free_tnode_lst(t_tree_node *head);
//libftwrap_utils.c
void	ft_perror(char *errtarget, char *errstr);
void ft_perror_and_exit(char *errtarget, char *errstr, int exit_status);
void	perror_and_exit(char *err_title, int exit_status);
char	*ft_xstrdup(const char *s1);
char	*ft_xstrtrim(const char *s1, const char *set);
char	*ft_xsubstr(const char *s, unsigned int start, size_t len);
char	*ft_xstrjoin(const char *s1, const char *s2);
char	**ft_xsplit(const char *s, char c);
//print_utils.c
void	wc(char *str);
void				print_to_last(char *begining, char *last);
void				print_tkn_lst(t_token *head);
void				print_init_of_tnode_lst(t_tree_node *tnode_ptr);
void				print_exec_of_tnode_lst(t_tree_node *tnode_ptr);
void				print_cmd_args(char **strs);
void				print_redir_lst(t_redir *head);
//syswrap_utils.c
void ft_free(void **ptr);
void	*ft_xmalloc(size_t size);
void	*ft_xrealloc(void *ptr, size_t size);
void	*ft_xcalloc(size_t count, size_t size);
int		ft_xdup2(int copied_fd, int dest_fd);
void	ft_xclose(int fd);
void	ft_xpipe(int *pipe_fd);
pid_t	ft_xfork(void);
void	ft_xexecve(char *cmd_path, char **cmd_args, char **envp);
//tkn_utils.c
void	remove_tkn(t_token **head, t_token *ptr, t_token *prev);
t_token		*find_last_valuable_tkn(t_token *head);
t_token *find_last_valuable_tkn_var2(t_token *head);
t_token		*find_prev_tkn(t_token *head, t_token *target);
t_token	*find_last_tkn(t_token *head);
void add_tkn_last(t_token **head, t_token *new);
char		*substr_from_tkn(t_token *begining, t_token *last);
//utils.c
char				*ulltonbase(unsigned long long num, unsigned int base);
size_t				ft2_strlcat(char *dest, const char *src, size_t size);
int					ft_strcmp(const char *s1, const char *s2);
//~~~~utils end~~~~

//~~~~ initi start~~~~
t_manager init(void);
//~~~~~~~~

//~~~~ tokenize start~~~~
t_token *tokenize(char *line_ptr);
t_token *make_new_tkn(char *begining, ssize_t count, enum e_token_kind kind);
static char *_substr_into_quote(char *begining, size_t count);

static enum e_token_kind	save_tkn_kind(char *begining);
static enum e_token_kind	save_redir_tkn_kind(char *begining);
static enum e_token_kind	save_env_or_text_kind(char *begining);

static ssize_t count_untill_last(char *begining);
ssize_t				count_untill_text_last(char *begining);
ssize_t				count_untill_ifs_last(char *begining);
ssize_t				count_untill_redir_last(char *begining);
ssize_t				count_untill_quote_last(char *begining);
ssize_t				count_untill_dollar_last(char *begining);
//~~~~~~~~

//~~~~ parse start~~~~
t_tree_node *parse(t_token *tkn_ptr);

void	remove_space_afrer_redir(t_token **tkn_head);

static t_tree_node *make_new_tnode(t_token *tkn_begining, t_token *tkn_ptr);
static void	add_tnode_last(t_tree_node **head, t_tree_node *new);
static t_tree_node	*find_last_tnode(t_tree_node *head);
static void	fill_null_last_tkn_of_tnode(t_tree_node *tnode_ptr);
static void	push_to_redir_tkns(t_tree_node *tnode_head);
static t_token *separate_and_make_redir_tkns_lst(t_token **cmd_tkns_head, t_bool (*is_func)(enum e_token_kind));
t_token	*push_redir_tkns_aaa(t_token **redir_tkns_head, t_token *first, t_token **cmd_tkns_head);
//~~~~~~~~

//~~~~expansion start~~~~
void	expansion(t_tree_node *ptr);

t_redir	*make_redir_lst(t_token *tkn_ptr);
static t_redir	*make_new_redir(t_token *begining, t_token *last);
static enum e_redir_kind	convert_redir_kind(t_token *begining);
static t_bool	contains_quote_tkn(t_token *begining);
static void	add_redir_last(t_redir **head_node, t_redir *new_node);
static t_redir	*find_last_redir(t_redir *head);

char **make_cmd_args(t_token *tkn_head);
static size_t count_arg_strs(t_token *tkn_ptr);

void	expansion_tkn_lst(t_token **tkn_head);
static t_token	*expand_env_of_tkn(t_token **dest_head, t_token *env_tkn, t_token *prev);
static t_token *tokenize_space_or_text(char *env_val);
static size_t count_untill_last_and_set_kind(char *begining, enum e_token_kind *kind);

char	*expand_env_in_dquote(char *str);
static size_t _strlen_env_expanded(char *str);
static size_t _strlcat_env_expanded(char *dest, char *str, size_t len);
//~~~~~~~~

//~~~~execute start~~~~
void	_exec(t_tree_node *ptr, t_manager *manager);
pid_t exec_external_cmd(t_exec_data data, t_manager *manager, t_bool last_cmd_flag);
void update_prev_fd(t_manager *manager, int *pipefd, t_bool last_cmd_flag);
t_bool change_outstream(t_redir *redir_head, int pipe_out_fd, t_bool last_cmd_flag);
t_bool change_instream(t_redir *redir_head, int prev_output_fd);
void	exec_cmd(char **cmd_args, char **envp);
static char	*search_and_make_path(char *cmd_name, char **envp);
t_bool	can_change_stream_to_redir(t_redir *redir_head, int dest_fd);
static int fd_find_last(t_redir *redir_ptr);
static int open_redir_path(t_redir *node);
#endif 