/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:52:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/03/27 05:48:01 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//__attribute__((destructor))
// static void destructor() {
//    system("leaks -q minishell");
//}

int	signal_flag = 0;

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
	rm_heredoc_tmp(tnode_head);
	free_tnode_list(tnode_head);
}

#include <string.h>
void	run_prompt(t_manager *manager)
{
	char *line;

	while (!signal_flag)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			//system("leaks -q minishell");
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

void handle_sigint_in_prompt(int num)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal_flag = 128 + num;
}

int main(void)
{
	t_manager manager;

	manager = initialize();
	signal(SIGINT, handle_sigint_in_prompt);
	signal(SIGQUIT, SIG_IGN);
	run_prompt(&manager);
	finalize(manager);
}