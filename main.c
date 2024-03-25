/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:52:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/03/26 03:53:54 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <stdio.h>

__attribute__((destructor))
 static void destructor() {
    system("leaks -q minishell");
}

void	process_line(char *line, t_manager *manager)
{
	t_token		*token_head;
	t_tree_node	*tnode_head;

	token_head = tokenize(line);
	if (token_head == NULL)
	{
		manager->exit_status = 1;
		return ; //errorを履くのはtokenize,ここに入るのは、エラーと""のとき
	}
	tnode_head = parse(token_head);
	expansion(tnode_head, *manager);
	try_heredoc(tnode_head, *manager);
	execute(tnode_head, manager);
	remove_tmpfile(tnode_head);
	free_tnode_list(tnode_head);
}

#include <string.h>
void	run_prompt(t_manager *manager)
{
	char *line;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			printf("NULLが来た\n");
			break;	
		}
		else if (strcmp(line, "") != 0)
		{
			add_history(line);
			//printf("line=%s;\n", line);
			process_line(line, manager);
		}
		free(line);
	}
}

//void handle_prompt_sigint(int num)
//{
//	printf("\n");
//	rl_on_new_line();
//	rl_replace_line("", 0);
//	rl_redisplay();
//}



int main(void)
{
	t_manager manager;

	manager = initialize();
	//signal(SIGINT, handle_prompt_sigint);
	//signal(SIGQUIT, SIG_IGN);
	run_prompt(&manager);
	finalize(manager);
}