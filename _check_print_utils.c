/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check_print_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:36:35 by toshi             #+#    #+#             */
/*   Updated: 2024/02/02 21:04:11 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


void	print_cmd_args(char **strs)
{
	size_t i = 0;
	while (strs[i] != NULL)
	{
		printf("%zd=%s\n", i, strs[i]);
		i++;
	}
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
void tkn_print_lst(t_token *head)
{
	t_token *ptr;
	
	ptr = head;
	while(ptr != NULL)
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
		// printf("next_add=%p;\n", ptr);
	}
}

void	tnode_print_lst(t_tree_node *tnode_ptr)
{
	size_t i;

	i = 0;
	while(tnode_ptr != NULL)
	{
		printf("----------tnode_ptr==%zd----------\n", i++);
		// printf("<cmd_tokens_ptr>\n");
		// tkn_print_lst(tnode_ptr->init_data.cmd_tokens);
		// if (tnode_ptr->init_data.infile_tokens != NULL)
		// {
		// 	printf("<infile_tkns>\n");
		// 	tkn_print_lst(tnode_ptr->init_data.infile_tokens);
		// }
		// if (tnode_ptr->init_data.outfile_tokens != NULL)
		// {
		// 	printf("<outfile_tkns>\n");
		// 	tkn_print_lst(tnode_ptr->init_data.outfile_tokens);
		// }
		if (tnode_ptr->exec_data.cmd_args)
		{
			print_cmd_args(tnode_ptr->exec_data.cmd_args);
		}
		if (tnode_ptr->exec_data.infile_paths)
		{
			redir_print_lst(tnode_ptr->exec_data.infile_paths);
		}
		if (tnode_ptr->exec_data.outfile_paths)
		{
			redir_print_lst(tnode_ptr->exec_data.outfile_paths);
		}
		tnode_ptr = tnode_ptr->right;
	}
}

//redir_listの内容をprint
void redir_print_lst(t_redir *head)
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