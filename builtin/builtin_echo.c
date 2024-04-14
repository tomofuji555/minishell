/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:45:02 by toshi             #+#    #+#             */
/*   Updated: 2024/04/14 17:59:13 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_bool	is_opt(char *str, char opt)
{
	size_t i;

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
	while (1)
	{
		ft_putstr_fd(cmd_args[i++], STDOUT_FILENO);
		if (cmd_args[i] == NULL)
			break ;
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!opt_n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

// int main(int argc, char **argv)
// {
// 	do_echo(argv);
// }