/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _print_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:36:35 by toshi             #+#    #+#             */
/*   Updated: 2024/02/15 09:15:33 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	wc(void)
{
	write(STDERR_FILENO, "test\n", 5);
}

//tokenizeの際、beginingとlastの範囲がとれているか
void print_to_last(char *begining, char *last)
{
	printf("%d==", (int)(last - begining + 1));
	while(begining != last)
	{
		printf("%c", *begining);
		begining++;
	}
	printf("%c;\n", *begining);
}

void	print_cmd_args(char **strs)
{
	size_t i = 0;
	while (strs[i] != NULL)
	{
		printf("%zd=%s\n", i, strs[i]);
		i++;
	}
}

//redir_listの内容をprint
void print_redir_lst(t_redir *head)
{
	t_redir *ptr;
	
	ptr = head;
	while(ptr != NULL)
	{	
		if (ptr->kind == REDIR_IN_FILE)
			printf("kind= IN;   val=%s;\n", ptr->val);
		else if (ptr->kind == REDIR_HEREDOC)
			printf("kind= HERE; val=%s;\n", ptr->val);
		else if (ptr->kind == REDIR_HEREDOC_NO_EXPAND)
			printf("kind= NOEX; val=%s;\n", ptr->val);
		else if (ptr->kind == REDIR_OUT_FILE)
			printf("kind= OUT;  val=%s;\n", ptr->val);
		else if (ptr->kind == REDIR_APPEND_FILE)
			printf("kind= APP;  val=%s;\n", ptr->val);
		ptr = ptr->next;
	}
}

//tokenの内容をprint
void print_tkn_lst(t_token *ptr)
{
	while (ptr != NULL)
	{	
		if (ptr->kind == TKN_SPACE)
			printf("kind= SPACE; val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_TEXT)
			printf("kind= TEXT;  val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_S_QUOTE)
			printf("kind= S_Q;   val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_D_QUOTE)
			printf("kind= D_Q;   val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_ENV)
			printf("kind= ENV;   val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_PIPE)
			printf("kind= PIPE;  val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_IN_FILE)
			printf("kind= IN;    val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_HEREDOC)
			printf("kind= HERE;  val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_OUT_FILE)
			printf("kind= OUT;   val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_APPEND_FILE)
			printf("kind= APP;   val=%s;\n", ptr->val);
		ptr = ptr->next;
	}
}

static void	print_init_data(t_tree_node *ptr)
{
	printf("<<init_data>>\n");
	if (ptr->init_data.cmd_tokens != NULL)
	{
		printf("<cmd>\n");
		print_tkn_lst(ptr->init_data.cmd_tokens);
	}
	if (ptr->init_data.infile_tokens != NULL)
	{
		printf("<infile>\n");
		print_tkn_lst(ptr->init_data.infile_tokens);
	}
	if (ptr->init_data.outfile_tokens != NULL)
	{
		printf("<outfile>\n");
		print_tkn_lst(ptr->init_data.outfile_tokens);
	}
}

static void	print_exec_data(t_tree_node	*ptr)
{
	printf("<<exec_data>>\n");
	if (ptr->exec_data.cmd_args)
	{
		printf("<cmd>\n");
		print_cmd_args(ptr->exec_data.cmd_args);
	}
	if (ptr->exec_data.infile_paths)
	{
		printf("<infile>\n");
		print_redir_lst(ptr->exec_data.infile_paths);
	}
	if (ptr->exec_data.outfile_paths)
	{
		printf("<outfile>\n");
		print_redir_lst(ptr->exec_data.outfile_paths);
	}
}

void	print_init_of_tnode_lst(t_tree_node *tnode_ptr)
{
	size_t i;

	i = 0;
	while(tnode_ptr != NULL)
	{
		printf("--------node_No==%zd--------\n", i++);
		print_init_data(tnode_ptr);
		tnode_ptr = tnode_ptr->right;
	}
}

void	print_exec_of_tnode_lst(t_tree_node *tnode_ptr)
{
	size_t i;

	i = 0;
	while(tnode_ptr != NULL)
	{
		printf("--------node_No==%zd--------\n", i++);
		print_exec_data(tnode_ptr);
		tnode_ptr = tnode_ptr->right;
	}
}

//void	print_tnode_lst(t_tree_node *tnode_ptr)
//{
//	size_t i;

//	i = 0;
//	while(tnode_ptr != NULL)
//	{
//		printf("--------node_No==%zd--------\n", i++);
//		print_init_data(tnode_ptr);
//		//print_exec_data(tnode_ptr);
//		tnode_ptr = tnode_ptr->right;
//	}
//}

