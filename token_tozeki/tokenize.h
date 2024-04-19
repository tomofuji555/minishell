/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:11:01 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 01:20:19 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

#include "../minishell.h"

t_token		*tokenize(char *line_ptr);
t_token		*make_new_tkn(char *begining, ssize_t count, enum e_token_kind kind);
ssize_t		count_text_last(char *begining);
ssize_t		count_ifs_last(char *begining);
ssize_t		count_redir_last(char *begining);
ssize_t		count_quote_last(char *begining);
ssize_t		count_dollar_last(char *begining);

#endif 