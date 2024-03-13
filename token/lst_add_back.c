/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:50:19 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/25 19:50:21 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

void	lst_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst)
	{
		if (*lst)
		{
			last = lstlast(*lst);
			last -> next = new;
		}
		else
			*lst = new;
	}
}
