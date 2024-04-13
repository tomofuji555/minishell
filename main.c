/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:52:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/08 14:07:59 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q minishell");
// }

int	signal_flag = 0;

void handle_sigint_in_prompt(int num)
{
	signal_flag = 128 + num;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	process_line(char *line, t_manager *manager)
{
	t_token		*token_head;
	t_tree_node	*tnode_head;

	token_head = tokenize(line);
	if (token_head == NULL)
	{
		update_exit_status(manager, 1);
		return ; //errorを履くのはtokenize,ここに入るのは、エラーと""のとき
	}
	tnode_head = parse(token_head);
	expansion(tnode_head, manager);
	manager->tmp_fd = ft_xdup(STDIN_FILENO); //xdupを作成する必要あり
	try_heredoc(tnode_head, manager);
	if (signal_flag == 0)
		execute(tnode_head, manager);
	else
		update_exit_status(manager, signal_flag);
	ft_xdup2(manager->tmp_fd, STDIN_FILENO);
	manager->prev_outfd = STDIN_FILENO;
	manager->last_cmd_flag = FALSE;
	manager->fork_count = 0;
	rm_heredoc_tmp(tnode_head);
	free_tnode_list(tnode_head);
	// signal_flag = 0; //mainでやっている
}

#include <string.h>
void	run_prompt(t_manager *manager)
{
	char *line;

	while (1)
	{
		signal_flag = 0;
		signal(SIGINT, handle_sigint_in_prompt);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell$ ");
		if (signal_flag != 0)
		{
			update_exit_status(manager, signal_flag);
			signal_flag = 0;
		}
		if (line == NULL)
			break;
		else if (strcmp(line, "") != 0)
		{
			add_history(line);
			process_line(line, manager);
		}
		free(line);
	}
}

int main(void)
{
	t_manager manager;

	manager = initialize();
	run_prompt(&manager);
	finalize(&manager);
}