/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:09:58 by toshi             #+#    #+#             */
/*   Updated: 2024/04/25 20:24:17 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../minishell.h"

//~~~~expansion start~~~~
void				expansion(t_tree_node *ptr, t_manager *manager);
char				*expand_env_in_dquote(char *str, t_manager *manager);
//expansion_env_tkn.c
t_token				*expand_env_token(t_token **head, t_token *env_tkn, \
					t_token *prev_env, t_manager *manager);
//expansion_env_in_dquote.c
char				*expand_env_in_dquote(char *str, t_manager *manager);
//substr_from_tkn.c
char				*substr_from_tkn(t_token *begining, t_token *last);
//make_cmd_args.c
char				**make_cmd_args(t_token *tkn_ptr);
//make_redir_list.c
t_redir				*make_redir_list(t_token *tkn_ptr);
//make_redir_list_utils.c
enum e_redir_kind	convert_redir_kind(t_token *first);

#endif