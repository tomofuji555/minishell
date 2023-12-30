/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valuable_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:13:27 by toshi             #+#    #+#             */
/*   Updated: 2023/12/31 00:13:28 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int is_valuable_token(enum e_token_kind kind)
{
	return (kind == TKN_TEXT || kind == TKN_S_QUOTE || kind == TKN_D_QUOTE || kind == TKN_ENV);
}