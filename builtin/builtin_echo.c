/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:45:02 by toshi             #+#    #+#             */
/*   Updated: 2024/04/21 20:26:23 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"

t_bool	is_opt(char *str, char opt)
{
	size_t	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] != '\0' && str[i] == opt)
			i++;
		if (str[i] == '\0' && i > 1)
			return (TRUE);
	}
	return (FALSE);
}

size_t	find_opt_start(char **cmd_arg, t_bool *opt_n_flag)
{
	size_t	i;

	i = 1;
	while (cmd_arg[i] != NULL && is_opt(cmd_arg[i], 'n'))
	{
		*opt_n_flag = TRUE;
		i++;
	}
	return (i);
}

int	do_echo(char **cmd_args)
{
	size_t	i;
	t_bool	opt_n_flag;

	opt_n_flag = FALSE;
	i = find_opt_start(cmd_args, &opt_n_flag);
	while (cmd_args[i] != NULL)
	{
		ft_putstr_fd(cmd_args[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!opt_n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
