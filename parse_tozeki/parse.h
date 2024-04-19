/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:35:15 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 00:52:49 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "../minishell.h"

t_tree_node *parse(t_token *tkn_ptr);
t_tree_node *make_tnode_list(t_token *tkn_ptr);
void		move_to_redir_tokens(t_tree_node *tnode_head);

#endif