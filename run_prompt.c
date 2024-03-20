/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:52:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/03/20 21:24:05 by tozeki           ###   ########.fr       */
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

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			printf("NULLが来た\n");
			break;	
		}
		else if (strcmp(line, "END") == 0)
		{
			free(line);
			break;
		}
		else if (strcmp(line, "") != 0)
		{
			add_history(line);
			printf("line=%s;\n", line);
		}
		free(line);
	}
}

void handle_prompt_sigquit(int num)
{
	return ;
}

void handle_prompt_sigint(int num)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(void)
{
	t_manager manager;

	//manager = init();
	signal(SIGINT, handle_prompt_sigint);
	//signal(SIGQUIT, handle_prompt_sigquit);
	//signal(SIGINT, SIG_IGN);
	run_prompt(&manager);
	// signal
	sleep(1);
	// finalize(manager);
}