/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:03:51 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 17:40:57 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../minishell.h"
#include "../libft/libft.h"

//envに＝がある前提で作成している
t_env	*make_new_env(char *envstr)
{
	char	*sep_ptr;
	t_env	*new;

	sep_ptr = ft_strchr(envstr, '=');
	new = (t_env *)ft_xmalloc(sizeof(t_env));
	new->key = ft_xsubstr(envstr, 0, (size_t)(sep_ptr - envstr));
	new->val = ft_xsubstr(sep_ptr, 1, \
				(size_t)(ft_strchr(envstr, '\0') - sep_ptr - 1));
	new->next = NULL;
	return (new);
}

static t_env	*_find_last_env(t_env *head)
{
	t_env	*ptr;

	ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	add_env_last(t_env **head, t_env *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	_find_last_env(*head)->next = new;
}
