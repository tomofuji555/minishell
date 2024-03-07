/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tkn_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:01:46 by toshi             #+#    #+#             */
/*   Updated: 2024/03/08 04:58:07 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//ここのNULLリターンは必要か審議
t_token	*find_last_tkn(t_token *head)
{
	t_token *ptr;

	if (head == NULL)
		return (NULL);
	ptr = head;
	while(ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

//ここのNULLリターンは必要か審議
t_token *find_last_valuable_tkn(t_token *head)
{
	t_token *ptr;

	if (head == NULL)
		return (NULL);
	ptr = head;
	while(ptr->next != NULL && is_valuable_tkn(ptr->next->kind))
		ptr = ptr->next;
	return (ptr);
}

// targetにheadが来ていたら、NULLが帰ってくる
// targetはlist内にないとクラッシュする
t_token *search_prev_tkn(t_token *head, t_token *target)
{
	t_token *ptr;

	if (head == target)
		return (NULL);
	ptr = head;
	while (ptr->next != target)
		ptr = ptr->next;
	return (ptr);
}

void add_tkn_last(t_token **head, t_token *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_tkn(*head)->next = new;
}

void	remove_tkn(t_token **head, t_token *target, t_token *prev)
{
	if (prev == NULL)
		*head = target->next;
	else
		prev->next = target->next;
	free_tkn(target);
}

static size_t	_strlen_from_tkn(t_token *begining, t_token *last)
{
	t_token	*ptr;
	size_t	i;
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

static size_t	_strlcpy_from_tkn(char *dest, t_token *src, size_t len)
{
	size_t	dest_i;
	size_t	val_i;

	dest_i = 0;
	while (dest_i + 1 < len && src != NULL)
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

char *substr_from_tkn(t_token *begining, t_token *last)
{
	size_t	len;
	char	*str;

	len = 1 + _strlen_from_tkn(begining, last);
	str = (char *)ft_xmalloc(sizeof(char) * len);
	_strlcpy_from_tkn(str, begining, len);
	return (str);
}
