/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:54:15 by tozeki            #+#    #+#             */
/*   Updated: 2024/03/26 20:58:53 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//void	update_pwd(t_manager *manager, char *new_pwd)
//{
//	free(manager->current_dir);
//	manager->current_dir = 
//}

typedef struct s_path
{
	char				*val;
	struct s_redir		*next;
}	t_path;

t_path	*make_new(char *first, char *last)
{
	t_path *new;

	new = (t_path *)malloc(sizeof(t_path));
	new->val = ft_xsubstr(first, 0, (size_t)(last - first));
	new->next = NULL;
	return (new);
}

t_path *make_path_list(char *ptr)
{
	t_path	*new;
	t_path	*head;
	char *last;

	head = NULL;
	while(ptr != '\0')
	{
		last = ft_strchr(ptr, '/');
		if (last == NULL)
			last = ft_strchr(ptr, '\0') - sizeof(char);
		new = make_new(ptr, last);
		ptr = last;
	}
}


char *expand_path(char *str, t_manager *manager)
{
	char *expanded_str;
	
	if (ft_strnstr(str, "./", ft_strlen(str)))
	{
		char *full_path = manager->current_dir;
		make_path_list(str);
	}
}

int	do_cd(char **cmd_args, t_manager *manager)
{
	if (cmd_args[2] != NULL)
	{
		perror_arg2("cd","too many arguments");
		return (1);
	}
	if (chdir(cmd_args[1]) == SYS_FAILURE)
	{
		perror("cd");
		return (1);
	}
	update_pwd(manager, cmd_args[1]);
	return (0);
}