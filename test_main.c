/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:25:58 by toshi             #+#    #+#             */
/*   Updated: 2024/04/12 18:47:35 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/parse.h"
#include "token/tokenize.h"
#include "minishell.h"

void	print_tree(t_tree_node *root)
{
	t_tree_node *ptr;
	size_t		i;

	ptr = root;
	while (ptr->left != NULL)
		ptr = ptr->left;
	i = 0;
	printf("------------ i=%zd ------------\n", i++);
	print_init_data(ptr);
	while (ptr != NULL)
	{
		printf("------------ i=%zd ------------\n", i++);
		if (ptr->right != NULL)
			print_init_data(ptr);
		ptr = ptr->prev;
	}
}

void	process_line(char *line)
{
	t_token		*token_head;
	t_tree_node	*tree_head;

	token_head = tokenize_wrap(line);
	if (token_head == NULL)
	{
		ft_putendl_fd("error", STDERR_FILENO);
		return ;
	}
	print_tkn_list(token_head);
	tree_head = parse_wrap(token_head);
	// print_tree(tree_head);
}

#include <string.h>
int	main()
{
	char *line;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break;
		else if (strcmp(line, "") != 0)
		{
			add_history(line);
			process_line(line);
		}
		free(line);
	}
}