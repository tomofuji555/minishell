/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:14:07 by toshi             #+#    #+#             */
/*   Updated: 2024/04/10 21:56:57 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	upsert_env_helper(t_manager *manager, char *str, char *env_name, char *sep_ptr)
{
	t_env *env_ptr;
	t_env *new;
	char *new_val;
	
	env_ptr = search_env(env_name, manager->env_list);
	if (env_ptr)
	{
		new_val = ft_substr(sep_ptr, 1, (size_t)(ft_strchr(str, '\0') - sep_ptr - sizeof(char)));
		free(env_ptr->val);
		env_ptr->val = new_val;
	}
	else
	{
		new = make_new_env(str);
		add_env_last(&(manager->env_list), new);
	}
}

t_bool	is_invalid_key(char *key)
{
	if (!(ft_isalpha(*key) || *key == '_'))
		return (TRUE);
	while (*key != '\0' && *key != '=')
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (TRUE);
		key++;
	}
	return (FALSE);
}

t_bool	validate_and_upsert_env(char *str, t_manager *manager)
{
	char *sep_ptr;
	char *env_name;
	
	sep_ptr = ft_strchr(str, '=');
	if (sep_ptr == NULL)
		sep_ptr = ft_strchr(str, '\0');
	env_name = ft_substr(str, 0, (size_t)(sep_ptr - str));
	if (is_invalid_key(env_name))
	{
		perror_arg3("export", env_name, "not a valid identifier");
		free(env_name);
		return (FALSE);
	}
	if (*sep_ptr == '=')
		upsert_env_helper(manager, str, env_name, sep_ptr);
	free(env_name);
	return (TRUE);
}

int	do_export(char **cmd_args, t_manager *manager)
{
	size_t	argc;
	t_bool	err_flag;
	size_t	i;

	argc = count_strs(cmd_args);
	if (argc == 1)
	{
		print_env_list(manager->env_list);
		return (0);
	}
	err_flag = FALSE;
	i = 1;
	while (i < argc)
	{
		if (!validate_and_upsert_env(cmd_args[i], manager))
			err_flag = TRUE;
		i++;
	}
	if (err_flag == TRUE)
		return (1);
	return (0);
}
