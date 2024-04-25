/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:03:06 by toshi             #+#    #+#             */
/*   Updated: 2024/04/25 16:44:12 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../utils/utils.h"

void	free_path_node(t_path *pnode)
{
	free(pnode->val);
	free(pnode);
}

void	free_path_list(t_path *head)
{
	t_path	*next_ptr;
	t_path	*ptr;

	if (head == NULL)
		return ;
	ptr = head;
	next_ptr = head->next;
	while (next_ptr != NULL)
	{
		free_path_node(ptr);
		ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free_path_node(ptr);
}

/// @brief ptr->valによって、current_pathを整形し直して、その複製を返す。渡した先で旧current_pathのfreeが必要
/// @return	../->current_dirの後ろから２番目の/までを抜き出し返す。見つからなかったらrootまで来てるため、/を返す
///	./->今のcurrent_pathを返す
///	/->/を返す
/// 文字列/->current_pathとjoinして返す 
char	*make_path(char *current_path, char *arg) //name
{
	char	*last_ptr;

	if (is_equal_str(arg, "./"))
		return (ft_xstrdup(current_path));
	else if (is_equal_str(arg, "/"))
		return (ft_xstrdup("/"));
	else if (is_equal_str(arg, "../"))
	{
		last_ptr = strchr_n_back(current_path, '/', 2);
		if (last_ptr == NULL)
			return (ft_xstrdup("/"));
		return (ft_xsubstr(current_path, 0, \
				(size_t)(last_ptr - current_path + 1)));
	}
	else
		return (ft_xstrjoin(current_path, arg));
}

//ptrがNULLじゃない前提で実装している
char	*make_full_path_helper(char *current_dir_slash, t_path *head) //name
{
	t_path	*ptr;
	char	*path;
	char	*tmp_path;

	path = make_path(current_dir_slash, head->val);
	ptr = head->next;
	while (ptr != NULL)
	{
		if (!(is_equal_str(ptr->val, "/") || is_equal_str(ptr->val, "./")))
		{
			tmp_path = path;
			path = make_path(path, ptr->val);
			free(tmp_path);
		}
		ptr = ptr->next;
	}
	return (path);
}

char	*make_full_path(char *arg_path, char *current_dir)
{
	t_path	*arg_path_list;
	char	*current_dir_slash;
	char	*full_path_slash;

	if (is_equal_str(arg_path, ""))
		return (ft_xstrjoin(current_dir, "/"));
	arg_path_list = make_path_list(arg_path);
	current_dir_slash = ft_xstrjoin(current_dir, "/");
	full_path_slash = make_full_path_helper(current_dir_slash, arg_path_list);
	free_path_list(arg_path_list);
	free(current_dir_slash);
	return (full_path_slash);
}
