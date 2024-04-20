/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:13:15 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 17:39:35 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../libft/libft.h"

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
