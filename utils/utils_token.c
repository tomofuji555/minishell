/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:01:46 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 17:40:23 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

//ここのNULLリターンは必要か審議
t_token	*find_last_valuable_token(t_token *head)
{
	t_token	*ptr;

	ptr = head;
	while (ptr->next != NULL && is_valuable_token(ptr->next->kind))
		ptr = ptr->next;
	return (ptr);
}

// targetにheadが来ていたら、NULLが帰ってくる
// targetはlist内にないとクラッシュする
// headがNULLの場合もクラッシュする
t_token	*search_prev_token(t_token *head, t_token *target)
{
	t_token	*ptr;

	if (head == target)
		return (NULL);
	ptr = head;
	while (ptr->next != target)
		ptr = ptr->next;
	return (ptr);
}

t_token	*find_last_token(t_token *head)
{
	t_token	*ptr;

	ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	add_token_last(t_token **head, t_token *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_token(*head)->next = new;
}

void	remove_token(t_token **head, t_token *target, t_token *prev)
{
	if (prev == NULL)
		*head = target->next;
	else
		prev->next = target->next;
	free_token(target);
}
