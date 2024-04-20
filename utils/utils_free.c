/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:12:15 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 17:36:28 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_multi_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free (strs[i]);
		i++;
	}
	free (strs);
}

void	free_token(t_token *tkn)
{
	free(tkn->val);
	free(tkn);
}

void	free_token_list(t_token *head)
{
	t_token	*next_ptr;
	t_token	*ptr;

	if (head == NULL)
		return ;
	ptr = head;
	next_ptr = head->next;
	while (next_ptr != NULL)
	{
		free_token(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_token(ptr);
}
