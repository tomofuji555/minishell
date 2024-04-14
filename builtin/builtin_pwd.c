/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:55:19 by toshi             #+#    #+#             */
/*   Updated: 2024/04/14 18:05:30 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int do_pwd(char **cmd_arg, t_manager *manager)
{
	ft_putendl_fd(manager->current_dir, STDOUT_FILENO);
	return (0);
}