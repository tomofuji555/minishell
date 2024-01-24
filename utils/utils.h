/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:27:24 by toshi             #+#    #+#             */
/*   Updated: 2024/01/14 23:57:19 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "../libft/libft.h"
#include "../execute.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

//utils_1.c
void		perror_and_exit(char *err_title, int exit_status);
size_t		ft2_strlcat(char *dest, const char *src, size_t size);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_xstrtrim(const char *s1, const char *set);
//tkn_utils.c
t_token		*find_last_node(t_token *head);
void		free_tkn(t_token *tkn);
//make_redir_list_utils.c
t_redir		*find_last_redir_node(t_redir *head);
void		add_redir_node_last(t_redir **head_node, t_redir *new_node);
enum e_redir_kind	convert_redir_kind(t_token *begining);
void		print_redir_token_list(t_redir *head);
//env_utils.c
size_t		count_envname(char *dollar_ptr);
char		*ft_getenv(const char *target_str);
char		*search_env_val(char *dollar_ptr, size_t env_name_len);
//bool_utils.c
t_bool		is_redir_token(enum e_token_kind kind);
t_bool		is_valuable_token(enum e_token_kind kind);
t_bool		is_ifs(char c);
t_bool		is_last_cmd(t_tree_node *cur_node);
//alloc_utils.c
void *		ft_xmalloc(size_t size);
void *		ft_xrealloc(void *ptr, size_t size);
void *		ft_xcalloc(size_t count, size_t size);
//fujiwa_utils.c
void		lst_add_back(t_token **lst, t_token *new);
t_token		*make_new_token(char *start, ssize_t mv_count, int token_kind);
t_token		*lstlast(t_token *lst);

#endif 