/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <username@student.your42netw      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:36:24 by username          #+#    #+#             */
/*   Updated: 2024/03/18 16:36:33 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include <stdbool.h>
#include <stdio.h>
#include "../minishell.h"

//typedef enum s_bool
//{
//	FALSE	= 0,
//	TRUE	= 1
//}	t_bool;

//typedef struct	s_tree_node
//{
//	t_init_arg_data		init_arg_data;
//	t_exec_arg_data		exec_arg_data;
//	struct s_tree_node	*prev;
//	struct s_tree_node	*left;
//	struct s_tree_node	*right;
//}	t_tree_node;

void		split_by_pipe(t_tree_node **tree, t_token **head, ssize_t count);
ssize_t		count_pipe(t_token *head);
t_token		*find_prev_last_pipe(t_token *head, ssize_t count);
t_token		*put_pipe_token(t_token **head, t_token *last_pipe, ssize_t count);
t_token		*find_last_pipe(t_token *head, ssize_t count);
t_tree_node	*prev_node(t_tree_node *prev_tree);
t_token		*cmd_of_ls(t_token **head, t_token **last_pipe);
t_tree_node	*init_ls_node(t_token **head, t_token *last_pipe, t_tree_node *prev_node);
t_tree_node	*ls_tree_node(t_token **head, t_tree_node *prev_node);
t_token		*rs_append_node_add_add_null(t_token **head, t_token *last_pipe);
t_token		*cmd_of_rs(t_token **head, t_token *last_pipe, t_bool is_first);
t_tree_node	*init_rs_node(t_token **head, t_token *last_pipe, t_bool is_first, t_tree_node *prev_node);
t_tree_node	*rs_tree_node(t_token **head, t_token *last_pipe, t_bool is_first, t_tree_node *prev_node);
void		print_syntax_error_free(t_token **head, t_token *error_token);
t_token		*next_cmd(t_token *current);
bool		is_syntax_error_pipe(t_token **head, t_token *current);
bool		is_syntax_error_redirect(t_token **head, t_token *current);
void		syntax_check(t_token **head);

#endif
