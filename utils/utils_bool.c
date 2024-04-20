/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:09 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 21:45:17 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../libft/libft.h"

t_bool	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_bool	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

t_bool	is_delim(char c)
{
	return (is_ifs(c) || is_quote(c) || c == '<' || c == '>' \
		|| c == '$' || c == '|');
}

t_bool	is_equal_str(const char *s1, char *s2)
{
	return (ft_strlen(s1) == ft_strlen(s2) && \
			ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
}

t_bool	is_cmd_node(t_tree_node *ptr)
{
	return (ptr->left == NULL && ptr->right == NULL);
}
