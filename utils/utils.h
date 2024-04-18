/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:07:59 by toshi             #+#    #+#             */
/*   Updated: 2024/04/18 20:53:06 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "../minishell.h"

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
void		print_env_list(t_env *ptr);
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
void		ft_xexecve(char *cmd_path, char **cmd_args, t_env *env_list);

size_t count_envvar(t_env *env_list);
char		**make_envp(t_env *env_list);
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

#endif 