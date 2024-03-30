/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:54:15 by tozeki            #+#    #+#             */
/*   Updated: 2024/03/31 06:26:59 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	update_pwd(t_manager *manager, char *full_path)
{
	free(manager->current_dir);
	manager->current_dir = full_path;
}

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

t_path	*make_new(char *first, char *last, t_bool flag)
{
	char	*tmp_val;
	t_path *new;

	new = (t_path *)malloc(sizeof(t_path));
	tmp_val = ft_xsubstr(first, 0, (size_t)(last - first + 1));
	if (flag)
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
	t_bool	flag;
	char *last;

	head = NULL;
	flag = FALSE;
	while (*ptr != '\0')
	{
		last = ft_strchr(ptr, '/');
		if (last == NULL)
		{
			last = ft_strchr(ptr, '\0') - sizeof(char);
			flag = TRUE;
		}
		new = make_new(ptr, last, flag);
		add_new_last(&head, new);
		ptr = last + sizeof(char);
	}
	return (head);
}

char *build_path(t_path *first, char *current_dir)
{
	char *last_ptr;
	
	if (is_equal_str(first->val, "./"))
		return (ft_xstrdup(current_dir)); //cuurent_dirを返す
	else if (is_equal_str(first->val, "/"))
		return (ft_xstrdup("/"));//スラッシュを返す
	else if (is_equal_str(first->val, "../"))
	{
		last_ptr = strchr_n_back(current_dir, '/', 2);
		if (last_ptr == NULL)
			return (ft_xstrdup("/"));
		return (ft_xsubstr(current_dir, 0, (size_t)(last_ptr + sizeof(char) - current_dir + 1))); //current_dirの最後から２個目のスラッシュまでを抜き出し返す
	}
	else
	{
		return (ft_xstrjoin(current_dir, first->val));
		// return (join_and_free_str2(current_dir, ft_xstrjoin("/", first->val))); //current_dir+(文字列)を返す
	}
}

char	*make_new_path(t_path *head, char *current_dir)
{
	t_path	*ptr;
	char	*full_path;
	char	*tmp_path;

	
	full_path = build_path(head, current_dir);
	ptr	= head->next;
	while (ptr != NULL)
	{
		if (is_equal_str(ptr->val, "/") || is_equal_str(ptr->val, "./"))
			;
		else
		{
			tmp_path = full_path;
			full_path = build_path(ptr, full_path);
			free(tmp_path);
		}
		ptr = ptr->next;
	}
	return (full_path);
}

char *expand_path(char *destpath, char *nowpath)
{
	char	*new_path;
	t_path	*dest_head;
	char	*nowpath_sla;
	
	nowpath_sla = ft_xstrjoin(nowpath, "/");
	dest_head = make_path_list(destpath);
	print_path_list(dest_head);
	new_path = make_new_path(dest_head, nowpath_sla); //freeする必要あり
	free_path_list(dest_head);
	free(nowpath_sla);
	printf("%s;\n", new_path);
	return (new_path);
}

size_t	count_strs(char **strs)
{
	size_t i;

	i = 1;
	while (strs[i] != NULL)
		i++;
	return (i);
}

int	do_cd(char **cmd_args, t_manager *manager)
{
	char *full_path;
	size_t argc;

	argc = count_strs(cmd_args);
	if (argc > 2)
	{
		perror_arg2("cd","too many arguments");
		return (1);
	}
	if (argc == 1)
		;//cd $HOMEと同じ動き
	else if (is_equal_str(cmd_args[1], "-"))
		;//cd $OLDPWDと同じ動き
	else
	{
		full_path = expand_path(cmd_args[1], manager->current_dir);
		if (chdir(full_path) == SYS_FAILURE)
		{
			perror("cd");
			return (1);
		}
	}
	update_pwd(manager, cmd_args[1]);
	return (0);
}