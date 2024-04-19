/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:01:30 by toshi             #+#    #+#             */
/*   Updated: 2024/04/19 22:06:46 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_env_node(t_env *env_node)
{
	free(env_node->key);
	free(env_node->val);
	free(env_node);
}

void	free_env_list(t_env *env_list)
{
	t_env *next_ptr;
	t_env *ptr;

	if (env_list == NULL)
		return ;
	ptr = env_list;
	next_ptr = env_list->next;
	while(next_ptr != NULL)
	{
		free_env_node(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_env_node(ptr);
}

void	free_redir_node(t_redir *redir_node)
{
	free(redir_node->val);
	free(redir_node);
}

void	free_redir_list(t_redir *head)
{
	t_redir *next_ptr;
	t_redir *ptr;

	if (head == NULL)
		return ;
	ptr = head;
	next_ptr = head->next;
	while(next_ptr != NULL)
	{
		free_redir_node(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_redir_node(ptr);
}
