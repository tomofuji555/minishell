/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_wrap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:11:11 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 17:32:30 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_token	*tokenize_wrap(char *line)
{
	t_token	*head;

	head = NULL;
	if (split_to_token(&head, line) == -1)
		return (NULL);
	return (head);
}
