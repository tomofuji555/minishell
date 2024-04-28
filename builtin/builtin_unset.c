/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:04:57 by toshi             #+#    #+#             */
/*   Updated: 2024/04/28 15:10:21 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../utils/utils.h"

static t_env	*search_prev_env(t_env *head, t_env *target)
{
	t_env	*ptr;

	if (head == target)
		return (NULL);
	ptr = head;
	while (ptr->next != target)
		ptr = ptr->next;
	return (ptr);
}

static void	remove_env(t_env **head, t_env *target)
{
	t_env	*prev;

	if (*head == NULL)
		return ;
	prev = search_prev_env(*head, target);
	if (prev)
		prev->next = target->next;
	else
		*head = target->next;
	free_env_node(target);
}

int	do_unset(char **cmd_args, t_manager *manager)
{
	size_t	argc;
	size_t	i;
	t_env	*env_ptr;

	argc = count_strs(cmd_args);
	if (argc == 1)
		return (0);
	i = 1;
	while (i < argc)
	{
		env_ptr = search_env(cmd_args[i], manager->env_list);
		if (env_ptr)
			remove_env(&(manager->env_list), env_ptr);
		i++;
	}
	return (0);
}
