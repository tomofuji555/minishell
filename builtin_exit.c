/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:24:13 by toshi             #+#    #+#             */
/*   Updated: 2024/03/31 17:12:29 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>


t_bool	is_numstr(char *ptr)
{
	if (*ptr == '\0')
		return (FALSE);
	while (*ptr != '\0')
	{
		if (!ft_isdigit(*ptr))
			return (FALSE);
		ptr++;
	}
	return (TRUE);
}

int do_exit(char **cmd_args, t_manager *manager)
{
	size_t argc;
	int num;

	argc = count_strs(cmd_args);
	if (argc == 1)
		exit (manager->exit_status);
	if (!is_numstr(cmd_args[1]) || is_longlong_over(cmd_args[1], &num))
	{
		perror_arg3("exit", cmd_args[1], "numeric argument required");
		exit (2);
	}
	else if (argc > 2)
	{
		perror_arg2("exit", "too many arguments");
		return (1);
	}
	exit ((unsigned char)num);
}