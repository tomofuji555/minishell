/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_from_tkn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:15:36 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 00:36:45 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

static size_t	_strlen_from_tkn(t_token *begining, t_token *last)
{
	t_token	*ptr;
	size_t	len;

	ptr = begining;
	len = 0;
	while(ptr != last->next)
	{
		len += ft_strlen(ptr->val);
		ptr = ptr->next;
	}
	return (len);
}

static size_t	_strlcat_from_tkn(char *dest, t_token *src, size_t len)
{
	size_t	dest_i;
	size_t	val_i;

	dest_i = 0;
	while (dest_i + 1 < len && src != NULL)
	{
		dest_i += strlcat_ret_catlen(dest, src->val, len);
		src = src->next;
	}
	dest[dest_i] = '\0';
	return (dest_i);
}
// val_i = 0;
// while (src->val[val_i] != '\0')
// {
// 	dest[dest_i] = src->val[val_i];
// 	dest_i++;
// 	val_i++;
// }

char *substr_from_tkn(t_token *begining, t_token *last)
{
	size_t	len;
	char	*str;

	len = _strlen_from_tkn(begining, last);
	str = (char *)ft_xmalloc(sizeof(char) * (len + 1));
	_strlcat_from_tkn(str, begining, (len + 1));
	return (str);
}