/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:54:15 by tozeki            #+#    #+#             */
/*   Updated: 2024/03/27 16:39:38 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// void	update_pwd(t_manager *manager, char *new_pwd)
// {
// 	free(manager->current_dir);
// 	manager->current_dir = 
// }

// typedef struct s_path
// {
// 	char				*val;
// 	struct s_redir		*next;
// }	t_path;

// t_path	*make_new(char *first, char *last)
// {
// 	t_path *new;

// 	new = (t_path *)malloc(sizeof(t_path));
// 	new->val = ft_xsubstr(first, 0, (size_t)(last - first));
// 	new->next = NULL;
// 	return (new);
// }

// t_path	*find_last_path(t_path *head)
// {
// 	t_path *ptr;

// 	ptr = head;
// 	while(ptr->next != NULL)
// 		ptr = ptr->next;
// 	return (ptr);
// }

// void add_path_last(t_path **head, t_path *new)
// {
// 	if (*head == NULL)
// 	{
// 		*head = new;
// 		return ;
// 	}
// 	find_last_path(*head)->next = new;
// }

// t_path *make_path_list(char *ptr)
// {
// 	t_path	*new;
// 	t_path	*head;
// 	char *last;

// 	head = NULL;
// 	while (ptr != '\0')
// 	{
// 		last = ft_strchr(ptr, '/');
// 		if (last == NULL)
// 			last = ft_strchr(ptr, '\0') - sizeof(char);
// 		new = make_new(ptr, last);
// 		add_new_last(&head, new);
// 		ptr = last + sizeof(char);
// 	}
// 	return (head);
// }

// char *make_first_path(t_path *first, char *current_dir)
// {
// 	if (is_equal_str(first->val, "./"))
// 		return (ft_xstrdup(current_dir)); //cuurent_dirを返す
// 	else if (is_equal_str(first->val, "/"))
// 		return (ft_xstrdup("/"));//スラッシュを返す
// 	else if (is_equal_str(first->val, "../"))
// 		return (ft_xsubstr(current_dir, 0, (size_t)(strchr_n_back(current_dir, '/', 2) - current_dir + 1))); //current_dirの最後から２個目のスラッシュまでを抜き出し返す
// 	else
// 		return (join_and_free_str2(current_dir, ft_xstrjoin("/", first->val))); //current_dir+/(文字列)を返す
// }

// char	*make_expanded_path(t_path *head, char *current_dir)
// {
// 	t_path	*ptr;
// 	char	*full_path;
// 	char	*tmp_path;

	
// 	full_path = make_first_path(head, current_dir);
// 	ptr	= head->next;
// 	while (ptr != NULL)
// 	{
// 		if (is_equal_str(ptr->val, "/") || is_equal_str(ptr->val, "./"))
// 			;
// 		else
// 		{
// 			tmp_path = full_path;
// 			full_path = make_first_path(ptr, current_dir);
// 			free(tmp_path);
// 		}
// 		ptr = ptr->next;
// 	}
// 	return (full_path);
// }

// char *expand_path(char *oldpath, t_manager *manager)
// {
// 	char	*new_path;
// 	t_path	*head;
	
// 	head = make_path_list(oldpath);
// 	new_path = make_expanded_path(head, manager->current_dir); //freeする必要あり
// 	//free_path_list(head);
// 	return (new_path);
// }

int	do_cd(char **cmd_args, t_manager *manager)
{
	char *full_path;
	
	if (cmd_args[2] != NULL)
	{
		perror_arg2("cd","too many arguments");
		return (1);
	}
	// full_path = expand_path(cmd_args[1], manager);
	if (chdir(cmd_args[1]) == SYS_FAILURE)
	{
		perror("cd");
		return (1);
	}
	// update_pwd(manager, cmd_args[1]);
	return (0);
}