/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_longlong_over.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:15:09 by toshi             #+#    #+#             */
/*   Updated: 2024/03/31 14:35:10 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

static size_t	get_start_set_sign(const char *str, int *psign)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		*psign = -1;
		i++;
	}
	return (i);
}

static size_t	get_end(const char *str, size_t i)
{
	while (str[i] != '\0' && ft_isdigit(str[i]) != 0)
		i++;
	return (i);
}

static long long	num_check(long long num, const char c, int sign)
{
	if (sign > 0)
	{
		if (num > (LLONG_MAX / 10))
			return (LLONG_MAX);
		else if (num == (LLONG_MAX / 10) && (c - '0') > (LLONG_MAX % 10))
			return (LLONG_MAX);
	}
	else if (sign < 0)
	{
		if (num < (LLONG_MIN / 10))
			return (LLONG_MIN);
		else if (num == (LLONG_MIN / 10) && (c - '0') > -(LLONG_MIN % 10))
			return (LLONG_MIN);
	}
	return (0);
}

t_bool	is_longlong_over(const char *str, int *ans_num)
{
	long long	num;
	int		sign;
	size_t	start;
	size_t	end;
	long long	overflow;

	num = 0;
	sign = 1;
	start = get_start_set_sign(str, &sign);
	end = get_end(str, start);
	while (start < end)
	{	
		overflow = num_check(num, str[start], sign);
		if (overflow != 0)
		{
			*ans_num = (int)2;
			return (TRUE);
		}
		num = (num * 10) + (sign * (str[start] - '0'));
		start++;
	}
	*ans_num = (int)num;
	return (FALSE);
}