/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:03:08 by toshi             #+#    #+#             */
/*   Updated: 2024/04/14 21:52:22 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../utils/utils.h"

int do_env(char **cmd_args, t_manager *manager)
{
	if (count_strs(cmd_args) != 1)
	{
		perror_arg2("env", "env with no options or arguments");
		return (1);
	}
	print_env_list(manager->env_list);
	return (0);
}