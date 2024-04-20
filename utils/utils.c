/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:59 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 17:33:08 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../libft/libft.h"

size_t	count_strs(char **strs)
{
	size_t	i;

	i = 1;
	while (strs[i] != NULL)
		i++;
	return (i);
}

void	update_exit_status(t_manager *manger, int num)
{
	free(manger->exit_status);
	manger->exit_status = ft_xitoa(num);
}

char	*join_and_free_str2(char *str1, char *str2)
{
	char	*joined_str;

	joined_str = ft_xstrjoin(str1, str2);
	free(str2);
	return (joined_str);
}

char	*strchr_n_back(char *str, char c, size_t n)
{
	size_t	c_count;
	size_t	len;

	if (n == 0)
		return (NULL);
	c_count = 0;
	len = ft_strlen(str);
	while (1)
	{
		if (str[len] == c)
			c_count++;
		if (len == 0 || n == c_count)
			break ;
		len--;
	}
	if (n == c_count)
		return (&(str[len]));
	return (NULL);
}

//帰りがコピーしたカウントを返すft_strlcat
size_t	strlcat_ret_catlen(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	if (dest_len > size)
		return (0);
	i = 0;
	while (src[i] != '\0' && dest_len + i + 1 < size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (i);
}
