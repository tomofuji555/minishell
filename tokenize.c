/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:51:12 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/25 19:51:14 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_token	*head;

  	head = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;	
		split_to_token (&head, line);
		while (head != NULL)
		{
			printf ("%s %d\n", head->val, head->kind);
			head = head->next;
		}
		if (*line)
			add_history(line);
		// TODO: intepret line as a command
		free_lst_all (head);
		free(line);
	}
	exit(0);
}

int	is_metachar(char c)
{
	if (c == ' ' || c == '<' || c == '>' \
		|| c == '|' || c == '$' \
		|| c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

t_token	*make_new_token(char *start, ssize_t mv_count, int token_kind)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->val = ft_substr (start, 0, mv_count);
	node->next = NULL;
	node->kind = token_kind;
	return (node);
}

void	make_token_list(t_token **head, char *start, ssize_t mv_count, int token_kind)
{
	t_token *new;

	new = make_new_token (start, mv_count, token_kind);	
	lst_add_back (head, new);
}

void split_to_token(t_token **head, char *line)
{
	ssize_t	mv_count;

	mv_count = 0;
	while (*line != '\0')	
	{
		if (*line == ' ')	
			mv_count = space_token (head, line);
		else if (*line == '>')
			mv_count = output_token (head, line);
		else if (*line == '<')
			mv_count = input_token (head, line);
		else if (*line == '|')
 			mv_count = pipe_token (head, line);
		else if (*line == '$')
	 		mv_count = env_token (head, line);
		else if (*line == '\'' || *line == '\"')
	 		mv_count = quort_token (head, line);
		else
			mv_count = text_token (head, line);
		line = line + mv_count;
	}
}

