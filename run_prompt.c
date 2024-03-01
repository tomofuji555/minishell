/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:52:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/03/02 03:30:20 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	parse_and_exec_line(char *line, t_manager *manager)
{
	t_token		*token_head;
	t_tree_node	*tnode_head;

	token_head = tokenize(line);
	if (token_head == NULL)
		return ;//エラーを吐きreturn、exitはしない
	tnode_head = parse(token_head);
	expansion(tnode_head);
	_exec(tnode_head, manager);
	free(line);
}


void	run_prompt(t_manager *manager)
{
	char *line;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			perror_and_exit("readline_error", 1);
		else if (ft_strcmp(line, "END") == 0)
		{
			free(line);
			break;
		}
		else
			parse_and_exec_line(line, manager);
	}	
}

int main(void)
{
	t_manager manager;

	manager = init();
	run_prompt(&manager);
	// finalize(manager);
}