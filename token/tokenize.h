/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:26:42 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/04/12 17:00:26 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "../minishell.h"

t_token	*lstlast(t_token *lst);
void	lst_add_back(t_token **lst, t_token *new);
ssize_t	split_to_token(t_token **head, char *line);
void	judge_token_type(t_token **node, char char1, char char2);
t_token	*make_new_token(char *start, ssize_t mv_count, int token_kind);
void	token_list(t_token **head, char *start, ssize_t count, int kind);
ssize_t	space_token(t_token **head, char *line);
void	free_lst_all(t_token **head);
ssize_t	text_token(t_token **head, char *line);
ssize_t	pipe_token(t_token **head, char *line);
ssize_t	quort_token(t_token **head, char *line);
ssize_t	output_token(t_token **head, char *line);
ssize_t	input_token(t_token **head, char *line);
ssize_t	quort_in_env(t_token **head, char *line);
ssize_t	env_token(t_token **head, char *line);
int		is_metachar(char c);
ssize_t	quort_error(char c);

t_token  *tokenize_wrap(char *line);

#endif
