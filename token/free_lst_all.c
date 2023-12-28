/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:49:29 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/27 23:35:21 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_lst_all(t_token **head)
{
	t_token *current;
	t_token *next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		if (current->val != NULL)
			free(current->val);
		free(current);
		current = next;
	}
	*head = NULL;
}

