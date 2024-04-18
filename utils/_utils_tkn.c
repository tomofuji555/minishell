/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_tkn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:01:46 by toshi             #+#    #+#             */
/*   Updated: 2024/04/18 22:16:17 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_token	*find_last_tkn(t_token *head)
{
	t_token *ptr;

	ptr = head;
	while(ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

//ここのNULLリターンは必要か審議
t_token *find_last_valuable_tkn(t_token *head)
{
	t_token *ptr;

	ptr = head;
	while(ptr->next != NULL && is_valuable_tkn(ptr->next->kind))
		ptr = ptr->next;
	return (ptr);
}

// targetにheadが来ていたら、NULLが帰ってくる
// targetはlist内にないとクラッシュする
// headがNULLの場合もクラッシュする
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
