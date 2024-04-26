/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:14:07 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 19:04:45 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

void	upsert_env(t_manager *manager, char *str)
{
	char	*sep_ptr;
	char	*env_name;
	t_env	*env_ptr;
	t_env	*new;

	sep_ptr = ft_strchr(str, '=');
	if (sep_ptr == NULL)
		return ;
	env_name = ft_xsubstr(str, 0, (size_t)(sep_ptr - str));
	env_ptr = search_env(env_name, manager->env_list);
	if (env_ptr)
	{
		free(env_ptr->val);
		env_ptr->val = ft_xsubstr(sep_ptr, 1, \
					(size_t)(ft_strchr(str, '\0') - sep_ptr - 1));
	}
	else
	{
		new = make_new_env(str);
		add_env_last(&(manager->env_list), new);
	}
	free(env_name);
}

static t_bool	is_valid_key(char *key)
{
	if (!(ft_isalpha(*key) || *key == '_'))
		return (FALSE);
	while (*key != '\0' && *key != '=')
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (FALSE);
		key++;
	}
	return (TRUE);
}

static t_bool	validate_key_and_upsert_env(char *str, t_manager *manager)
{
	char	*sep_ptr;
	char	*env_name;

	sep_ptr = ft_strchr(str, '=');
	if (sep_ptr == NULL)
		sep_ptr = ft_strchr(str, '\0');
	env_name = ft_xsubstr(str, 0, (size_t)(sep_ptr - str));
	if (!is_valid_key(env_name))
	{
		perror_arg3("export", env_name, "not a valid identifier");
		free(env_name);
		return (FALSE);
	}
	if (*sep_ptr == '=')
		upsert_env(manager, str);
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
		print_sorted_env(manager->env_list);
		return (0);
	}
	err_flag = FALSE;
	i = 1;
	while (i < argc)
	{
		if (!validate_key_and_upsert_env(cmd_args[i], manager))
			err_flag = TRUE;
		i++;
	}
	if (err_flag == TRUE)
		return (1);
	return (0);
}
