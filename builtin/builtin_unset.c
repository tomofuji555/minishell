/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:04:57 by toshi             #+#    #+#             */
/*   Updated: 2024/04/14 13:22:11 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../utils/utils.h"

// targetはlist内にないとクラッシュする
// headがNULLの場合もクラッシュする
t_env	*search_prev_env(t_env *head, t_env *target)
{
	t_env	*ptr;

	if (head == target)
		return (NULL);
	ptr = head;
	while (ptr->next != target)
		ptr = ptr->next;
	return (ptr);
}

void	remove_env(t_env **head, t_env *target)
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
	print_env_list(*head);
}

int	do_unset(char **cmd_args, t_manager *manager)
{
	size_t	argc;
	size_t	i;
	t_env	*envvar;

	argc = count_strs(cmd_args);
	if (argc == 1)
		return (0);
	i = 1;
	while (i < argc)
	{
		envvar = search_env(cmd_args[i], manager->env_list);
		if (envvar)
			remove_env(&(manager->env_list), envvar);
		i++;
	}
	return (0);
}