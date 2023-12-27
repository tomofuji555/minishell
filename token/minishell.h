/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/19 16:46:17 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//#include <cstddef>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

enum e_token_kind
{
	TKN_SPACE,
	TKN_TEXT,
	TKN_S_QUOTE,
	TKN_D_QUOTE,
	TKN_ENV,
	TKN_PIPE,
	TKN_IN_FILE,
	TKN_HERE_DOC,
	TKN_OUT_FILE,
	TKN_APPEND_FILE,
};

typedef struct s_token
{
	enum e_token_kind	kind;
	char				*val;
	struct s_token		*next;
}	t_token;

typedef struct s_tree_node
{
	t_token			*cmd_tokens;
	t_token			*infile_tokens;
	t_token			*outfile_tokens;
	struct s_node	*prev;
	struct s_node	*left;
	struct s_node	*right;
}	t_tree_node;

char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
t_token	*lstlast(t_token *lst);
void	lst_add_back(t_token **lst, t_token *new);
void	split_to_token(t_token **head, char *line);
void	judge_token_type(t_token **node, char char1, char char2);
t_token	*make_new_token(char *start, ssize_t mv_count, int token_kind);
void	token_list(t_token **head, char *start, ssize_t count, int kind);
ssize_t	space_token(t_token **head, char *line);
void	free_lst_all(t_token *head);
ssize_t	text_token(t_token **head, char *line);
ssize_t	pipe_token(t_token **head, char *line);
ssize_t	quort_token(t_token **head, char *line);
ssize_t	output_token(t_token **head, char *line);
ssize_t	input_token(t_token **head, char *line);
ssize_t	quort_in_env(t_token **head, char *line);
ssize_t	env_token(t_token **head, char *line);
int		is_metachar(char c);
void	quort_error(t_token *head);

#endif
