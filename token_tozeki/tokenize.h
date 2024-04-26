/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:11:01 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 19:36:26 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include	"../minishell.h"

t_token		*tokenize(char *line_ptr);
t_token		*make_new_token(char *begining, ssize_t count, \
				enum e_token_kind kind);
ssize_t		count_text_last(char *begining);
ssize_t		count_ifs_last(char *begining);
ssize_t		count_redir_last(char *begining);
ssize_t		count_quote_last(char *begining);
ssize_t		count_dollar_last(char *begining);

#endif 