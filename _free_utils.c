/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _free_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:12:15 by toshi             #+#    #+#             */
/*   Updated: 2024/02/08 08:30:01 by tozeki           ###   ########.fr       */
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

void	free_tkn_lst(t_token *head)
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

void	free_tnode(t_tree_node 	*tnode)
{
	free_tkn_lst(tnode->init_data.cmd_tokens);
	if (tnode->init_data.infile_tokens)
		free_tkn_lst(tnode->init_data.infile_tokens);
	if (tnode->init_data.outfile_tokens)
		free_tkn_lst(tnode->init_data.outfile_tokens);
	free(tnode);
}

void	free_tnode_lst(t_tree_node *head)
{
	t_tree_node *next_ptr;
	t_tree_node *ptr;

	if (head == NULL)
		return;
	ptr = head;
	next_ptr = head->right;
	while(next_ptr != NULL)
	{
		free_tnode(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->right;
	}
	free_tnode(ptr);
}