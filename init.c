/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:37:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/03/05 18:24:22 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"execute.h"

//export envpの+1でmalloc->copy。最後に指定の文字列を追加。
//char **export(char **envp, char *add_envvar)
//ok AAA=
//ko AAA

//unset envpの-1でmalloc->copy
//char **unset(char **envp, char *rm_envvar_name)
//環境変数にない文字列が来たら何もしない

//t_manager *get_manager()
//{
//	static t_manager *manager;
//	static size_t i = 0;

//	if (i == 0)
//		manager = init();
//	return (manager);
//}

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

//envに＝がある前提で作成している
t_env *make_new_enode(char *envvar)
{
	t_env	*new;

	new = (t_env *)ft_xmalloc(sizeof(t_env));
	new->original = ft_xstrdup(envvar);
	new->key = ft_xsubstr(envvar, 0, (size_t)(ft_strchr(envvar, '=') - envvar));
	new->val = ft_xsubstr(ft_strchr(envvar, '=') + sizeof(char), 0, (size_t)(ft_strchr(envvar, '\0') - ft_strchr(envvar, '=') - 1));
	new->printed_flag = FALSE;
	new->next = NULL;
	return (new);
}

t_env *find_last_enode(t_env *head)
{
	t_env	*ptr;

	ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void add_enode_last(t_env **head, t_env *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_enode(*head)->next = new;
}

t_env *make_env_list()
{
	extern char **environ;
	size_t i;
	t_env	*head;
	t_env	*new;

	i = 0;
	while(environ[i] != NULL)
	{
		new = make_new_enode(environ[i]);
		add_enode_last(&head, new);
		i++;
	}
	return (head);
}

t_manager init(void)
{
	t_manager manager;

	manager.exit_status = 0;
	manager.env_list = make_env_list();
	manager.prev_output_fd = STDIN_FILENO;
	return (manager);
}
