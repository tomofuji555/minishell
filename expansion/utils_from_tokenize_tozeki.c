/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_from_tokenize_tozeki.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:16:20 by tozeki            #+#    #+#             */
/*   Updated: 2024/05/03 00:16:08 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../utils/utils.h"
#include "../libft/libft.h"

ssize_t	count_ifs_last(char *first)
{
	ssize_t	i;

	i = 1;
	while (first[i] && is_ifs(first[i]))
		i++;
	return (i);
}

//閉じクォートが来ないで文末に来た場合、-1を返す
ssize_t	count_quote_last(char *first)
{
	ssize_t	i;

	i = 1;
	while (first[i] && first[0] != first[i])
		i++;
	if (first[i] == '\0')
		return (-1);
	return (i + 1);
}

//最初の文字がalphaか_以外ならそこで区切り、1を返す
// ex) $$ $? $6 $@
//文字中の数字、_、文字が対象->alnum+_か
static ssize_t	count_env_last(char *ptr)
{
	ssize_t	count;
	
	if (!(ft_isalpha(*ptr) || *ptr == '_'))
		return (1);
	count = 0;
	while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
	{
		count++;
		ptr++;
	}
	return (count);
}

//nextがクォートなら、1($)+クォートのカウント
//nextが$以外のdelimなら、1($)のみ
//nextがalphaか_以外なら2($+next)
ssize_t	count_dollar_last(char *first)
{
	char	*next;
	ssize_t	count;

	next = first + sizeof(char);
	if (is_quote(*next))
	{
		count = count_quote_last(next);
		if (count == -1)
			return (-1);
		return (1 + count);
	}
	if (is_delim(*next) && *next != '$')
		return (1);
	return (1 + count_env_last(next));
}
