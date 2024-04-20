/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:55:19 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 17:55:47 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"

int	do_pwd(t_manager *manager)
{
	ft_putendl_fd(manager->current_dir, STDOUT_FILENO);
	return (0);
}
