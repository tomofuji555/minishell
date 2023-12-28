/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:51:12 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/28 00:08:18 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//__attribute__((destructor))
//static void destructor() {
	//system("leaks -q minishell");
//}

int	main(void)
{
	char	*line;
	t_token	*head;
	t_token	*current;

	head = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (split_to_token (&head, line) < 0)
			free_lst_all (&head);
		else
		{
			current = head;
			while (current != NULL)
			{
				printf ("%s %d\n", current->val, current->kind);
				current = current->next;
			}
			if (*line)
				add_history(line);
			free_lst_all (&head);
		}
		free (line);
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
	t_token *node;

    node = (t_token *)malloc(sizeof(t_token));
    if (node == NULL)
        return (NULL);
    node->val = ft_substr(start, 0, mv_count);
    if (node->val == NULL)
    {
        free(node);
        return (NULL);
    }
    node->next = NULL;
    node->kind = token_kind;
    return (node);
}

void	token_list(t_token **head, char *start, ssize_t count, int kind)
{
	t_token	*new;

	new = make_new_token (start, count, kind);
	if (!new)
		return ;
	lst_add_back (head, new);
}

ssize_t	split_to_token(t_token **head, char *line)
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
		if (mv_count < 0)
			return (-1);
	}
	return (1);
}
