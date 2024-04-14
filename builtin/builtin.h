/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:16:16 by toshi             #+#    #+#             */
/*   Updated: 2024/04/14 17:53:46 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

#include "../minishell.h"

typedef struct s_path
{
	char				*val;
	struct s_path		*next;
}	t_path;

//~~~~ cd ~~~~
int		do_cd(char **cmd_args, t_manager *manager);
char	*make_full_path(char *arg_path, char *current_dir);
t_path	*make_path_list(char *path_ptr);
void	print_path_list(t_path *ptr);
//~~~~~~~~

//~~~~exit start~~~~
t_bool	is_longlong_over(const char *str, int *ans_num);
int do_exit(char **cmd_args, t_manager *manager);
//~~~~~~~~


int		do_export(char **cmd_args, t_manager *manager);
void	upsert_env(t_manager *manager, char *str);

int		do_env(char **cmd_args, t_manager *manager);

int		do_unset(char **cmd_args, t_manager *manager);

#endif