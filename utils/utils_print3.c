/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:13:15 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 17:07:16 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../libft/libft.h"

void	print_init_of_tnode_list(t_tree_node *ptr)
{
	size_t	i;

	i = 0;
	while (ptr != NULL)
	{
		printf("--------node_No==%zd--------\n", i++);
		print_init_data(ptr);
		ptr = ptr->right;
	}
}

void	print_adv_of_tnode_list(t_tree_node *ptr)
{
	size_t	i;

	i = 0;
	while (ptr != NULL)
	{
		printf("--------node_No==%zd--------\n", i++);
		if (is_cmd_node(ptr))
			print_adv_data(ptr);
		else
		{
			printf("<<pipe>>\n");
		}
		ptr = ptr->right;
	}
}

void	print_env_list(t_env *ptr)
{
	while (ptr != NULL)
	{
		ft_putstr_fd(ptr->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(ptr->val, STDOUT_FILENO);
		ptr = ptr->next;
	}
}
