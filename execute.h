/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/04/12 15:37:30 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

#define	SYS_FAILURE	-1
#define	CHILD		0
#define EXIST		0
#define NOT_EXIST	-1
#define DEFAULT		0
#define AMBIGUOUS	NULL

extern int	signal_flag;

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

typedef struct s_env
{
	char				*original;
	char				*key;
	char				*val;
	t_bool				printed_flag;
	struct s_env		*next;
}	t_env;

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

typedef struct s_manager
{
	t_env	*env_list;
	char	*current_dir;
	char	*exit_status;
	int		tmp_fd;
	int		heredoc_line;
	int		prev_outfd;
	size_t	fork_count;
	pid_t	last_pid;
	t_bool	last_cmd_flag;
}	t_manager;

//~~~~utils start~~~~
//bool_utils.c
t_bool		is_ifs(char c);
t_bool		is_quote(char c);
t_bool		is_delim(char c);
t_bool		is_valuable_tkn(enum e_token_kind kind);
t_bool		is_in_redir_tkn(enum e_token_kind kind);
t_bool		is_out_redir_tkn(enum e_token_kind kind);
t_bool		is_redir_tkn(enum e_token_kind kind);
t_bool		is_last_cmd(t_tree_node *ptr);
t_bool		is_first_cmd(t_tree_node *ptr);
t_bool		is_cmd_node(t_tree_node *ptr);
t_bool		is_cmd_path(char *first_cmd_arg);
t_bool		is_equal_str(const char *s1, char *s2);
t_bool		is_builtin(char *cmd);
t_bool		is_single_builtin(t_tree_node *tnode_ptr);
//env_utils.c
size_t		count_envname(char *dollar_ptr);
t_env		*search_env(char *name, t_env *env_list);
char		*ms_getenv(const char *env_name, t_manager *manager);
char		*getenv_in_str(char *dollar_ptr, size_t env_name_len, t_manager *manager);
//free_utils.c
void		free_multi_strs(char **strs);
void		free_tkn(t_token *tkn);
void		free_tkn_list(t_token *head);
void		free_env_node(t_env *env_node);
void		free_env_list(t_env *env_list);
void		free_init_data(t_init_data init_data);
void		free_tnode_list(t_tree_node *head);
//libftwrap_utils.c
void		perror_arg2(char *errtarget, char *errstr);
void		perror_arg3(char *s1, char *s2, char *s3);
void		perror_arg2_and_exit(char *errtarget, char *errstr, int exit_status);
void		perror_and_exit(char *err_title, int exit_status);
char		*ft_xstrdup(const char *s1);
char		*ft_xstrtrim(const char *s1, const char *set);
char		*ft_xsubstr(const char *s, unsigned int start, size_t len);
char		*ft_xstrjoin(const char *s1, const char *s2);
char		**ft_xsplit(const char *s, char c);
char		*ft_xitoa(int n);
//print_utils.c
void		wc(char *str);
void		print_to_last(char *begining, char *last);
void		print_tkn_list(t_token *head);
void		print_env_list(t_env *head);
void		print_cmd_args(char **strs);
void		print_redir_list(t_redir *head);
void		print_init_of_tnode_list(t_tree_node *tnode_ptr);
void		print_exec_of_tnode_list(t_tree_node *tnode_ptr);
//syswrap_utils.c
void		ft_free(void **ptr);
void		*ft_xmalloc(size_t size);
void		*ft_xrealloc(void *ptr, size_t size);
void		*ft_xcalloc(size_t count, size_t size);
int			ft_xdup(int copied_fd);
int			ft_xdup2(int copied_fd, int dest_fd);
void		ft_xclose(int fd);
void		ft_xpipe(int *pipefd);
pid_t		ft_xfork(void);
int			ft_xunlink(char *pathname);
void		ft_xexecve(char *cmd_path, char **cmd_args, t_env *env_list);
//tkn_utils.c
t_token		*find_last_tkn(t_token *head);
t_token		*find_last_valuable_tkn(t_token *head);
t_token		*search_prev_tkn(t_token *head, t_token *target);
void		add_tkn_last(t_token **head, t_token *new);
void		remove_tkn(t_token **head, t_token *ptr, t_token *prev);
char		*substr_from_tkn(t_token *begining, t_token *last);
//utils.c
size_t		strlcat_ret_catlen(char *dest, const char *src, size_t size);
char		*join_and_free_str1(char *str1, char *str2);
char		*join_and_free_str2(char *str1, char *str2);
char 		*strchr_n_back(char *str, char c, size_t n);
size_t		count_strs(char **strs);
void	update_exit_status(t_manager *manger, int num);
//~~~~utils end~~~~

//~~~~ initi start~~~~
t_env *make_new_env(char *envvar);
t_manager initialize(void);
void	finalize(t_manager *manager);
//~~~~~~~~

//~~~~ tokenize start~~~~
t_token		*tokenize(char *line_ptr);

t_token		*make_new_tkn(char *begining, ssize_t count, enum e_token_kind kind);
ssize_t		count_untill_ifs_last(char *begining);
ssize_t		count_untill_dollar_last(char *begining);
//~~~~~~~~

//~~~~ parse start~~~~
t_tree_node *parse(t_token *tkn_ptr);
//~~~~~~~~

//~~~~expansion start~~~~
void	expansion(t_tree_node *ptr, t_manager *manager);
char	*expand_env_in_dquote(char *str, t_manager *manager);
//~~~~~~~~

//~~~~execute start~~~~
void	exec_cmd_in_child(t_tree_node *ptr, t_manager *manager);
void	execute(t_tree_node *root, t_manager *manager);
//~~~~~~~~

//~~~~heredoc start~~~~
void	rm_heredoc_tmp(t_tree_node *tnode_head);
void	try_heredoc(t_tree_node *tnode_head, t_manager *manager);
//~~~~~~~~

//~~~~cd start~~~~
int	do_cd(char **cmd_args, t_manager *manager);
char *expand_path(char *oldpath, char *newpath);
//~~~~~~~~

//~~~~exit start~~~~
t_bool	is_longlong_over(const char *str, int *ans_num);
int do_exit(char **cmd_args, t_manager *manager);
//~~~~~~~~


int	do_export(char **cmd_args, t_manager *manager);
void add_env_last(t_env **head, t_env *new);
void	upsert_env(t_manager *manager, char *str);

int do_env(char **cmd_args, t_manager *manager);

int	do_unset(char **cmd_args, t_manager *manager);

#endif 