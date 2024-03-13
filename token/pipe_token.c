/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:50:45 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/25 19:50:47 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

ssize_t	pipe_token(t_token **head, char *line)
{
	token_list (head, line, 1, TKN_PIPE);
	return (1);
}
