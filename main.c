/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:52:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/19 23:41:55 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/utils.h"
#include "token_tozeki/tokenize.h"
#include "parse_tozeki/parse.h"
#include "expansion/expansion.h"
#include "execute/execute.h"

int	signal_flag = 0;

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q minishell");
// }

void _handle_sigint_in_prompt(int num)
{
	signal_flag = 128 + num;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/// @brief  token_head == NULLに入る時は、quote_errのみ??と""/''/(スペースのみ)は??
///
void	_process_line(char *line, t_manager *manager)
{
	t_token		*token_head;
	t_tree_node	*tnode_head;

	token_head = tokenize(line);
	if (token_head == NULL)
	{
		update_exit_status(manager, 1);
		return ;
	}
	tnode_head = parse(token_head);
	expansion(tnode_head, manager);
	manager->tmp_fd = ft_xdup(STDIN_FILENO);
	print_adv_of_tnode_list(tnode_head);
	// execute(tnode_head, manager);
	ft_xdup2(manager->tmp_fd, STDIN_FILENO);
	free_tnode_list(tnode_head);
}

#include <string.h>
void	_run_prompt(t_manager *manager)
{
	char *line;

	while (1)
	{
		signal_flag = 0;
		signal(SIGINT, _handle_sigint_in_prompt);
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
			_process_line(line, manager);
		}
		free(line);
	}
}

int main(void)
{
	t_manager manager;

	manager = initialize();
	_run_prompt(&manager);
	finalize(&manager);
}