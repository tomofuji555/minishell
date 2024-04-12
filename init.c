/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:37:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/12 15:38:23 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"execute.h"

//envに＝がある前提で作成している
t_env *make_new_env(char *envstr)
{
	char 	*sep_ptr;
	t_env	*new;

	sep_ptr = ft_strchr(envstr, '=');
	new = (t_env *)ft_xmalloc(sizeof(t_env));
	new->key = ft_xsubstr(envstr, 0, (size_t)(sep_ptr - envstr));
	new->val = ft_xsubstr(sep_ptr, 1, (size_t)(ft_strchr(envstr, '\0') - sep_ptr - 1));
	new->next = NULL;
	//
	new->printed_flag = FALSE;
	new->original = ft_xstrdup(envstr);
	//
	return (new);
}

static t_env *find_last_env(t_env *head)
{
	t_env	*ptr;

	ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void add_env_last(t_env **head, t_env *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_env(*head)->next = new;
}

static t_env *make_env_list()
{
	extern char **environ;
	size_t i;
	t_env	*head;
	t_env	*new;

	head = NULL;
	i = 0;
	while(environ[i] != NULL)
	{
		new = make_new_env(environ[i]);
		add_env_last(&head, new);
		i++;
	}
	return (head);
}

char	*get_current_dir(void)
{
	char *buf;

	buf = (char *)ft_xcalloc(PATH_MAX + 1, sizeof(char));
	getcwd(buf, PATH_MAX + 1);
	return (buf);
}

t_manager initialize(void)
{
	t_manager manager;

	manager.env_list = make_env_list();
	manager.current_dir = get_current_dir();
	manager.exit_status = ft_xitoa(0);
	manager.prev_outfd = STDIN_FILENO;
	manager.fork_count = 0;
	manager.last_cmd_flag = FALSE;
	manager.heredoc_line = 0;
	return (manager);
}

void	finalize(t_manager *manager)
{
	free_env_list(manager->env_list);
	free(manager->current_dir);
	free(manager->exit_status);
}

//size_t	count_strs_2(char **strs)
//{
//	size_t i;
	
//	i = 0;
//	while(strs[i] != NULL)
//		i++;
//	return (i);
//}

//char **init_envp(void)
//{
//	extern char **environ;
//	char	**new_envp;
//	size_t	i;
//	size_t	j;
//	size_t	str_count;

//	str_count = count_strs_2(environ);
//	new_envp = (char **)ft_xmalloc((str_count + 1) * sizeof(char *));
//	i = 0;
//	j = 0;
//	while(i < str_count)
//	{
//		new_envp[i++] = ft_xstrdup(environ[j]);
//		j++;
//	}
//	new_envp[i] = NULL;
//	return (new_envp);
//}
