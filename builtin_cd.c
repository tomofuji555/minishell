/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:54:15 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/08 22:09:05 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

typedef struct s_path
{
	char				*val;
	struct s_path		*next;
}	t_path;

void	print_path_list(t_path *ptr)
{
	while(ptr != NULL)
	{
		printf("val=%s;\n", ptr->val);
		ptr = ptr->next;
	}
}

void	free_pnode(t_path *pnode)
{
	free(pnode->val);
	free(pnode);
}

void	free_path_list(t_path *head)
{
	t_path *next_ptr;
	t_path *ptr;

	if (head == NULL)
		return ;
	ptr = head;
	next_ptr = head->next;
	while(next_ptr != NULL)
	{
		free_pnode(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_pnode(ptr);
}

t_path	*make_new(char *first, char *last, t_bool no_slash_flag)
{
	char	*tmp_val;
	t_path *new;

	new = (t_path *)malloc(sizeof(t_path));
	tmp_val = ft_xsubstr(first, 0, (size_t)(last - first + 1));
	if (no_slash_flag)
	{
		new->val = ft_xstrjoin(tmp_val, "/") ;
		free(tmp_val);
	}
	else
		new->val = tmp_val;
	new->next = NULL;
	return (new);
}

t_path	*find_last_path(t_path *head)
{
	t_path *ptr;

	ptr = head;
	while(ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void add_new_last(t_path **head, t_path *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_path(*head)->next = new;
}

t_path *make_path_list(char *ptr)
{
	t_path	*new;
	t_path	*head;
	t_bool	no_slash_flag;
	char *last;

	head = NULL;
	no_slash_flag = FALSE;
	while (*ptr != '\0')
	{
		last = ft_strchr(ptr, '/');
		if (last == NULL)
		{
			last = ft_strchr(ptr, '\0') - sizeof(char);
			no_slash_flag = TRUE;
		}
		new = make_new(ptr, last, no_slash_flag);
		add_new_last(&head, new);
		ptr = last + sizeof(char);
	}
	return (head);
}

/// @brief ptr->valによって、current_pathを整形し直して、その複製を返す。渡した先で旧current_pathのfreeが必要
/// @return	../->current_dirの後ろから２番目の/までを抜き出し返す。見つからなかったらrootまで来てるため、/を返す
///	./->今のcurrent_pathを返す
///	/->/を返す
/// 文字列/->current_pathとjoinして返す 
char *add_path(t_path *ptr, char *current_path)
{
	char *last_ptr;
	
	if (is_equal_str(ptr->val, "./"))
		return (ft_xstrdup(current_path));
	else if (is_equal_str(ptr->val, "/"))
		return (ft_xstrdup("/"));
	else if (is_equal_str(ptr->val, "../"))
	{
		last_ptr = strchr_n_back(current_path, '/', 2);
		if (last_ptr == NULL)
			return (ft_xstrdup("/"));
		return (ft_xsubstr(current_path, 0, (size_t)(last_ptr + sizeof(char) - current_path + 1))); 
	}
	else
		return (ft_xstrjoin(current_path, ptr->val));
}
// return (join_and_free_str2(current_dir, ft_xstrjoin("/", first->val))); //current_dir+(文字列)を返す

char	*make_absolute_path_helper(t_path *head, char *current_dir)
{
	t_path	*ptr;
	char	*full_path;
	char	*tmp_path;

	full_path = add_path(head, current_dir);
	ptr	= head->next;
	while (ptr != NULL)
	{
		if (is_equal_str(ptr->val, "/") || is_equal_str(ptr->val, "./"))
			;
		else
		{
			// printf("fullpath=%s;\n", full_path);
			tmp_path = full_path;
			full_path = add_path(ptr, full_path);
			free(tmp_path);
		}
		ptr = ptr->next;
	}
	return (full_path);
}

char *make_absolute_path(char *dest_path, char *current_dir)
{
	t_path	*dest_path_list;
	char	*current_dir_sla;
	char	*absolute_path;
	
	if (is_equal_str(dest_path, ""))
		return (ft_xstrjoin(current_dir, "/"));
	dest_path_list = make_path_list(dest_path);
	// print_path_list(dest_path_list);
	current_dir_sla = ft_xstrjoin(current_dir, "/");
	absolute_path = make_absolute_path_helper(dest_path_list, current_dir_sla);
	free_path_list(dest_path_list);
	free(current_dir_sla);
	return (absolute_path);
}

void	update_current_dir(t_manager *manager, char *path)
{
	free(manager->current_dir);
	manager->current_dir = ft_xsubstr(path, 0, ft_strlen(path) - 1);
}

int	do_cd(char **cmd_args, t_manager *manager)
{
	char	*path;
	size_t	argc;

	argc = count_strs(cmd_args);
	if (argc != 2)
	{
		perror_arg2("cd","too many arguments");
		return (1);
	}
	path = make_absolute_path(cmd_args[1], manager->current_dir); //このpathはfree必須
	wc(path);
	if (chdir(path) == SYS_FAILURE)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(cmd_args[1]);
		return (1);
	}
	update_current_dir(manager, path);
	free(path);
	// system("leaks -q minishell");
	return (0);
}
	// if (argc == 1)
	// {
	// 	path = ft_getenv("HOME", manager);
	// 	if (path == NULL)
	// 	{
	// 		perror_arg2("cd", "HOME not set");
	// 		return (1);
	// 	}
	// }
	// else if (is_equal_str(cmd_args[1], "-"))
	// {
	// 	path = ft_getenv("OLDPWD", manager);
	// 	if (path == NULL)
	// 	{
	// 		perror_arg2("cd", "OLDPWD not set");
	// 		return (1);
	// 	}
	// }
	// else