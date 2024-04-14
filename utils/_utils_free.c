/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:12:15 by toshi             #+#    #+#             */
/*   Updated: 2024/04/14 12:40:09 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

void	free_init_data(t_init_data init_data)
{
	if (init_data.cmd_tokens)
		free_tkn_list(init_data.cmd_tokens);
	if (init_data.infile_tokens)
		free_tkn_list(init_data.infile_tokens);
	if (init_data.outfile_tokens)
		free_tkn_list(init_data.outfile_tokens);
}

void	free_adv_data_and_tnode(t_tree_node 	*tnode)
{
	if (tnode->adv_data.cmd_args)
		free_multi_strs(tnode->adv_data.cmd_args);
	if (tnode->adv_data.infile_paths)
		free_redir_node_list(tnode->adv_data.infile_paths);	
	if (tnode->adv_data.outfile_paths)
		free_redir_node_list(tnode->adv_data.outfile_paths);
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
		free_adv_data_and_tnode(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->right;
	}
	free_adv_data_and_tnode(ptr);
}
