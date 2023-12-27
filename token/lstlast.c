/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstlast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:50:27 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/25 19:50:29 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lstlast(t_token *lst)
{
	t_token	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current -> next != NULL)
		current = current -> next;
	return (current);
}
