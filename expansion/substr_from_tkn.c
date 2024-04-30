/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_from_tkn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:15:36 by toshi             #+#    #+#             */
/*   Updated: 2024/04/30 01:17:58 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

static size_t	strlen_from_tkn(t_token *first, t_token *last)
{
	size_t	len;

	len = 0;
	while (first != last->next)
	{
		len += ft_strlen(first->val);
		first = first->next;
	}
	return (len);
}

static size_t	strlcpy_from_tkn(char *dest, t_token *src, size_t len)
{
	size_t	dest_i;
	size_t	val_i;

	dest_i = 0;
	while (src != NULL && dest_i + 1 < len)
	{
		val_i = 0;
		while (src->val[val_i] != '\0')
		{
			dest[dest_i] = src->val[val_i];
			dest_i++;
			val_i++;
		}
		src = src->next;
	}
	dest[dest_i] = '\0';
	return (dest_i);
}

char	*substr_from_tkn(t_token *first, t_token *last)
{
	size_t	len;
	char	*str;

	len = strlen_from_tkn(first, last);
	str = (char *)ft_xcalloc(len + 1, sizeof(char));
	strlcpy_from_tkn(str, first, (len + 1));
	return (str);
}
