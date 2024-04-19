/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:36:18 by toshi             #+#    #+#             */
/*   Updated: 2024/04/19 20:33:00 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../libft/libft.h"

void	perror_arg2(char *s1, char *s2)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(s2, STDERR_FILENO);
}

void	perror_arg3(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(s3, STDERR_FILENO);
}

void	perror_and_exit(char *s, int exit_status)
{
	perror(s);
	exit(exit_status);
}

void	perror_arg2_and_exit(char *s1, char *s2, int exit_status)
{
	perror_arg2(s1, s2);
	exit(exit_status);
}
