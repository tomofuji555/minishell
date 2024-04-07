/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:36:35 by toshi             #+#    #+#             */
/*   Updated: 2024/04/07 21:14:32 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	wc(char *str)
{
	if (str == NULL)
	{
		ft_putendl_fd("test", STDERR_FILENO);	
		return ;
	}
	ft_putendl_fd(str, STDERR_FILENO);
	//write(STDERR_FILENO, "test\n", 5);
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

//tokenの内容をprint
void print_tkn_list(t_token *ptr)
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

void	print_env_list(t_env *head)
{
	t_env	*ptr;

	ptr = head;
	while (ptr != NULL)
	{
		//printf("%s\n", ptr->original);
		printf("%s=%s\n", ptr->key, ptr->val);
		ptr = ptr->next;
	}
}

void	print_cmd_args(char **strs)
{
	size_t i = 0;
	while (strs[i] != NULL)
	{
		printf("%zd=%s;\n", i, strs[i]);
		i++;
	}
}

//redir_listの内容をprint
void print_redir_list(t_redir *head)
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

static void	print_base_data(t_tree_node *ptr)
{
	printf("<<base_data>>\n");
	if (ptr->base_data.cmd_tokens != NULL)
	{
		printf("<cmd>\n");
		print_tkn_list(ptr->base_data.cmd_tokens);
	}
	if (ptr->base_data.infile_tokens != NULL)
	{
		printf("<infile>\n");
		print_tkn_list(ptr->base_data.infile_tokens);
	}
	if (ptr->base_data.outfile_tokens != NULL)
	{
		printf("<outfile>\n");
		print_tkn_list(ptr->base_data.outfile_tokens);
	}
}

void	print_refine_data(t_tree_node	*ptr)
{
	
	printf("<<refine_data>>\n");
	if (ptr->refine_data.cmd_args)
	{
		printf("<cmd>\n");
		print_cmd_args(ptr->refine_data.cmd_args);
	}
	if (ptr->refine_data.infile_paths)
	{
		printf("<infile>\n");
		print_redir_list(ptr->refine_data.infile_paths);
	}
	if (ptr->refine_data.outfile_paths)
	{
		printf("<outfile>\n");
		print_redir_list(ptr->refine_data.outfile_paths);
	}
}

void	print_init_of_tnode_list(t_tree_node *tnode_ptr)
{
	size_t i;

	i = 0;
	while(tnode_ptr != NULL)
	{
		printf("--------node_No==%zd--------\n", i++);
		print_base_data(tnode_ptr);
		tnode_ptr = tnode_ptr->right;
	}
}

void	print_exec_of_tnode_list(t_tree_node *tnode_ptr)
{
	size_t i;

	i = 0;
	while(tnode_ptr != NULL)
	{
		printf("--------node_No==%zd--------\n", i++);
		if (is_cmd_node(tnode_ptr))
			print_refine_data(tnode_ptr);
		else
		{
			printf("<<pipe>>\n");
			//print_refine_data(tnode_ptr);
		}
		tnode_ptr = tnode_ptr->right;
	}
}

//void	print_tnode_list(t_tree_node *tnode_ptr)
//{
//	size_t i;

//	i = 0;
//	while(tnode_ptr != NULL)
//	{
//		printf("--------node_No==%zd--------\n", i++);
//		print_base_data(tnode_ptr);
//		print_refine_data(tnode_ptr);
//		tnode_ptr = tnode_ptr->right;
//	}
//}

//void	print_tnode_list(t_tree_node *tnode_ptr)
//{
//	size_t i;

//	i = 0;
//	while(tnode_ptr != NULL)
//	{
//		printf("--------node_No==%zd--------\n", i++);
//		print_base_data(tnode_ptr);
//		//print_refine_data(tnode_ptr);
//		tnode_ptr = tnode_ptr->right;
//	}
//}

