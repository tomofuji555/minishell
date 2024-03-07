/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _free_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:12:15 by toshi             #+#    #+#             */
/*   Updated: 2024/03/08 06:22:21 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	free_multi_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free (strs[i]);
		i++;
	}
	free (strs);
}

void	free_tkn(t_token *tkn)
{
	free(tkn->val);
	free(tkn);
}

void	free_tkn_list(t_token *head)
{
	t_token *next_ptr;
	t_token *ptr;

	if (head == NULL)
		return ;
	ptr = head;
	next_ptr = head->next;
	while(next_ptr != NULL)
	{
		free_tkn(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_tkn(ptr);
}

void	free_env_node(t_env *env_node)
{
	free(env_node->key);
	free(env_node->val);
	free(env_node->original);
	free(env_node);
}

void	free_env_list(t_env *env_list)
{
	t_env *next_ptr;
	t_env *ptr;

	if (env_list == NULL)
		return ;
	ptr = env_list;
	next_ptr = env_list->next;
	while(next_ptr != NULL)
	{
		free_env_node(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_env_node(ptr);
}

void	free_redir_node(t_redir *redir_node)
{
	free(redir_node->val);
	free(redir_node);
}

void	free_redir_node_list(t_redir *head)
{
	t_redir *next_ptr;
	t_redir *ptr;

	if (head == NULL)
		return ;
	ptr = head;
	next_ptr = head->next;
	while(next_ptr != NULL)
	{
		free_redir_node(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_redir_node(ptr);
}

void	free_base_data(t_base_data base_data)
{
	if (base_data.cmd_tokens)
		free_tkn_list(base_data.cmd_tokens);
	if (base_data.infile_tokens)
		free_tkn_list(base_data.infile_tokens);
	if (base_data.outfile_tokens)
		free_tkn_list(base_data.outfile_tokens);
}

void	free_refine_data_and_tnode(t_tree_node 	*tnode)
{
	if (tnode->refine_data.cmd_args)
		free_multi_strs(tnode->refine_data.cmd_args);
	if (tnode->refine_data.infile_paths)
		free_redir_node_list(tnode->refine_data.infile_paths);	
	if (tnode->refine_data.outfile_paths)
		free_redir_node_list(tnode->refine_data.outfile_paths);
	free(tnode);
}

void	free_tnode_list(t_tree_node *head)
{
	t_tree_node *next_ptr;
	t_tree_node *ptr;

	if (head == NULL)
		return;
	ptr = head;
	next_ptr = head->right;
	while(next_ptr != NULL)
	{
		free_refine_data_and_tnode(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->right;
	}
	free_refine_data_and_tnode(ptr);
}
