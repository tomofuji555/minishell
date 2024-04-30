/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:52:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/05/01 06:25:32 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/utils.h"
#include "token/tokenize.h"
#include "parse/parse.h"
#include "expansion/expansion.h"
#include "execute/execute.h"

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q minishell");
// }

static void	handle_sigint_in_prompt(int num)
{
	g_signal_flag = 128 + num;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/// @brief  tkn_list == NULLに入る時は、quote_errのみ??と""/''/(スペースのみ)は??
static void	process_line(char *line, t_manager *manager)
{
	t_token		*tkn_list;
	t_tree_node	*tree_list;

	tkn_list = tokenize(line);
	if (tkn_list == NULL)
	{
		update_exit_status(manager, 1);
		return ;
	}
	tree_list = parse(tkn_list);
	expansion(tree_list, manager);
	print_tree(tree_list);
	// execute(tree_list, manager);
	free_tree(tree_list);
}

static void	run_prompt(t_manager *manager)
{
	char	*line;

	while (1)
	{
		g_signal_flag = 0;
		signal(SIGINT, handle_sigint_in_prompt);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell$ ");
		if (g_signal_flag != 0)
		{
			update_exit_status(manager, g_signal_flag);
			g_signal_flag = 0;
		}
		if (line == NULL)
			break ;
		else if (!is_equal_str(line, ""))
		{
			add_history(line);
			process_line(line, manager);
		}
		free(line);
	}
}

int	main(void)
{
	t_manager	manager;

	g_signal_flag = 0;
	manager = initialize();
	run_prompt(&manager);
	finalize(&manager);
}
