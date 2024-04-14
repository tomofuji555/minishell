/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanson.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:09:58 by toshi             #+#    #+#             */
/*   Updated: 2024/04/14 00:15:24 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

#include "../minishell.h"

//~~~~expansion start~~~~
void	expansion(t_tree_node *ptr, t_manager *manager);
char	*expand_env_in_dquote(char *str, t_manager *manager);
//~~~~~~~~

#endif