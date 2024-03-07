/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:52:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/03/08 05:39:51 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

__attribute__((destructor))
 static void destructor() {
    system("leaks -q a.out");
}

//void	process_line(char *line, t_manager *manager)
//{
//	t_token		*token_head;
//	t_tree_node	*tnode_head;

//	token_head = tokenize(line);
//	if (token_head == NULL)
//	{
//		manager->exit_status = 1;
//		return ; //errorを履くのはtokenize,ここに入るのは、エラーと""のとき
//	}
//	tnode_head = parse(token_head);
//	expansion(tnode_head, *manager);
//	_exec(tnode_head, manager);
//	free_tnode_list(tnode_head);
//}

#include <string.h>
void	run_prompt(t_manager *manager)
{
	char *line;

	while (line != NULL)
	{
		line = readline("minishell$ ");
		if (strcmp(line, "END") == 0)
		{
			if (strcmp(line, "END") == 0)
				free(line);
			break ;
		}
		if (strcmp(line, "") != 0)
		{
			add_history(line);
			printf("line=%s;\n", line);
		}
		free(line);
	}
}

int main(void)
{
	t_manager manager;

	//manager = init();
	run_prompt(&manager);
	// finalize(manager);
}