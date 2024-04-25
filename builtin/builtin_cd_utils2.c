/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:39:44 by toshi             #+#    #+#             */
/*   Updated: 2024/04/25 16:47:17 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

void	print_path_list(t_path *ptr)
{
	while (ptr != NULL)
	{
		printf("val=%s;\n", ptr->val);
		ptr = ptr->next;
	}
}

t_path	*make_new(char *first, char *last, t_bool no_slash_flag) //name
{
	char	*tmp_val;
	t_path	*new;

	new = (t_path *)ft_xmalloc(sizeof(t_path));
	tmp_val = ft_xsubstr(first, 0, (size_t)(last - first + 1));
	if (no_slash_flag)
	{
		new->val = ft_xstrjoin(tmp_val, "/");
		free(tmp_val);
	}
	else
		new->val = tmp_val;
	new->next = NULL;
	return (new);
}

t_path	*find_last_path(t_path *head)
{
	t_path	*ptr;

	ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	add_new_last(t_path **head, t_path *new) //name
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_path(*head)->next = new;
}

t_path	*make_path_list(char *path_ptr)
{
	t_path	*new;
	t_path	*head;
	t_bool	no_slash_flag;
	char	*last;

	head = NULL;
	no_slash_flag = FALSE;
	while (*path_ptr != '\0')
	{
		last = ft_strchr(path_ptr, '/');
		if (last == NULL)
		{
			last = ft_strchr(path_ptr, '\0') - sizeof(char);
			no_slash_flag = TRUE;
		}
		new = make_new(path_ptr, last, no_slash_flag);
		add_new_last(&head, new);
		path_ptr = last + sizeof(char);
	}
	return (head);
}
