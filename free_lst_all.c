/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:49:29 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/25 19:49:32 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_all(t_token *head)
{
	t_token	*current = head;
	t_token	*nextNode;

	while (current != NULL)
	{
        	nextNode = current->next;
        	free(current);
		current = nextNode;
    }
}
