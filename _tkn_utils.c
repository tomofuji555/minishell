/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tkn_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:01:46 by toshi             #+#    #+#             */
/*   Updated: 2024/02/22 12:10:20 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//// //save_last~系は必ずptr->next!=NULLで止める
//t_token *first_space_skip_and_find_last_valuable_tkn(t_token *tkn_ptr)
//{
//	while(tkn_ptr != NULL && tkn_ptr->kind == TKN_SPACE)
//		tkn_ptr = tkn_ptr->next;
//	if (tkn_ptr != NULL)
//	{
//		while(tkn_ptr->next != NULL && is_valuable_tkn(tkn_ptr->next->kind))
//			tkn_ptr = tkn_ptr->next;
//	}
//	return (tkn_ptr);
//}

// //save_last~系は必ずptr->next!=NULLで止める
// t_token *find_last_valuable_tkn(t_token *tkn_ptr)
// {
// 	while(tkn_ptr->next != NULL && tkn_ptr->kind == TKN_SPACE)
// 		tkn_ptr = tkn_ptr->next;
// 	while(tkn_ptr->next != NULL && is_valuable_tkn(tkn_ptr->next->kind))
// 		tkn_ptr = tkn_ptr->next;
// 	return (tkn_ptr);
// }


// targetにheadが来ていたら、NULLが帰ってくる
// targetはlst内にある前提で終わらす
t_token *find_prev_tkn(t_token *head, t_token *target)
{
	t_token *ptr;

	if (head == target)
		return (NULL);
	ptr = head;
	while (ptr->next != target)
		ptr = ptr->next;
	return (ptr);
}

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
		i = 0;
		while(ptr->val[i] != '\0')
			i++;
		len += i;
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
	// printf("dest_i == %zd\n", dest_i);
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
	// printf("last->val == %s;  len == %zd\n", last->val, len);
	return (str);
}
