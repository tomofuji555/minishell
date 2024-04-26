/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:07:59 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 16:55:03 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

//bool_utils.c
t_bool	is_ifs(char c);
t_bool	is_quote(char c);
t_bool	is_delim(char c);
t_bool	is_equal_str(const char *s1, char *s2);
t_bool	is_cmd_node(t_tree_node *ptr);
//bool_utils2.c
t_bool	is_valuable_token(enum e_token_kind kind);
t_bool	is_in_redir_tkn(enum e_token_kind kind);
t_bool	is_out_redir_tkn(enum e_token_kind kind);
t_bool	is_redir_tkn(enum e_token_kind kind);
//env_utils.c
char	*ms_getenv(const char *env_name, t_manager *manager);
t_env	*search_env(char *name, t_env *env_list);
size_t	count_env(t_env *env_list);
char	**make_envp(t_env *env_list);
//env_utils2.c
t_env	*make_new_env(char *envstr);
void	add_env_last(t_env **head, t_env *new);
//error_utils.c
void	perror_arg2(char *s1, char *s2);
void	perror_arg3(char *s1, char *s2, char *s3);
void	perror_and_exit(char *s, int exit_status);
void	perror_arg2_and_exit(char *s1, char *s2, int exit_status);
//free_utils.c
void	free_multi_strs(char **strs);
void	free_token(t_token *tkn);
void	free_token_list(t_token *head);
//free_utils2.c
void	free_env_node(t_env *env_node);
void	free_env_list(t_env *env_list);
void	free_redir_node(t_redir *redir_node);
void	free_redir_list(t_redir *head);
//free_utils3.c
void	free_init_data(t_tree_node *ptr);
void	free_adv_data(t_tree_node *tnode);
void	free_tree_node(t_tree_node *ptr);
void	free_tnode_list(t_tree_node *head);
void	free_tree(t_tree_node *root);
//libftwrap_utils.c
char	*ft_xstrdup(const char *s1);
char	*ft_xstrtrim(const char *s1, const char *set);
char	*ft_xsubstr(const char *s, unsigned int start, size_t len);
char	*ft_xstrjoin(const char *s1, const char *s2);
char	*ft_xitoa(int n);
//libftwrap_utils2.c
char	**ft_xsplit(const char *s, char c);
//print_utils.c
void	wc(char *str);
void	print_to_last(char *first, char *last);
void	print_token_list(t_token *ptr);
void	print_cmd_args(char **strs);
void	print_redir_list(t_redir *head);
//print_utils2.c
void	print_init_data(t_tree_node *ptr);
void	print_adv_data(t_tree_node	*ptr);
void	print_tree(t_tree_node *root);
//print_utils3.c
void	print_init_of_tnode_list(t_tree_node *tnode_ptr);
void	print_adv_of_tnode_list(t_tree_node *tnode_ptr);
void	print_env_list(t_env *ptr);
//syswrap_utils.c
void	*ft_xmalloc(size_t size);
void	*ft_xrealloc(void *ptr, size_t size);
void	*ft_xcalloc(size_t count, size_t size);
int		ft_xdup(int copied_fd);
int		ft_xdup2(int copied_fd, int dest_fd);
//syswrap_utils2.c
void	ft_free(void **ptr);
void	ft_xclose(int fd);
void	ft_xpipe(int *pipefd);
pid_t	ft_xfork(void);
void	ft_xexecve(char *cmd_path, char **cmd_args, t_env *env_list);
//tkn_utils.c
t_token	*find_last_valuable_token(t_token *head);
t_token	*search_prev_token(t_token *head, t_token *target);
t_token	*find_last_token(t_token *head);
void	add_token_last(t_token **head, t_token *new);
void	remove_token(t_token **head, t_token *target, t_token *prev);
//utils.c
size_t	count_strs(char **strs);
void	update_exit_status(t_manager *manger, int num);
char	*join_and_free_str2(char *str1, char *str2);
char	*strchr_n_back(char *str, char c, size_t n);
size_t	strlcat_ret_catlen(char *dest, const char *src, size_t size);

#endif 