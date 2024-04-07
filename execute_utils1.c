/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:06:56 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/07 15:53:19 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */


//int	do_builtin(char **cmd_args, char **envp)
//{
//	if (!cmd_args)
//		return (-1);
//	if (is_equal_str(*cmd_args, "echo"))
//		return (ms_echo(cmd_args));
//	else if (is_equal_str(*cmd_args, "cd"))
//		rerurn (ms_cd(cmd_args, envp));
//	else if (is_equal_str(*cmd_args, "pwd"))
//		return (ms_pwd(envp));
//	else if (is_equal_str(*cmd_args, "export"))
//		return (ms_export(cmd_args, envp));
//	else if (is_equal_str(*cmd_args, "unset"))
//		return (ms_unset(cmd_args, envp));
//	else if (is_equal_str(*cmd_args, "env"))
//		return (ms_env(envp));
//	else if (is_equal_str(*cmd_args, "exit"))
//		return (ms_exit(cmd_args, envp));
//	else
//		return (-1);
//}

//t_bool	can_change_iostream_redirect(t_refine_data data)
//{
//	if (data.infile_paths)
//	{
//		if (!can_change_stream_redirect(data.infile_paths, STDIN_FILENO))
//			return (FALSE);
//	}
//	if (data.outfile_paths)
//	{
//		if (!can_change_stream_redirect(data.outfile_paths, STDOUT_FILENO))
//			return (FALSE);
//	}
//	return (TRUE);
//}

//void do_single_builtin(t_refine_data data, t_manager *manager)
//{
//	int tmpfd_in;
//	int tmpfd_out;

//	tmpfd_in = STDIN_FILENO;
//	tmpfd_out = STDOUT_FILENO;
//	if (can_change_iostream_redirect(data))
//		manager->exit_status = do_builtin(data.cmd_args, manager->env_list);
//	else
//		manager->exit_status = 1;
//	ft_xdup2(tmpfd_in, STDIN_FILENO);
//	ft_xdup2(tmpfd_out, STDOUT_FILENO);
//}

t_bool	try_do_builtin_and_eixt()
{
	int status;

	status = do_builtin();
	if (status == -1)
		return (FALSE);
	exit(status);
	return (TRUE);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

//static t_exec_data init_exec_data(void)
//{
//	t_exec_data data;

//	data.fork_count = 0;
//	data.last_cmd_flag = FALSE;
//	data.last_pid = -1;
//	data.prev_outfd = STDIN_FILENO;
//	return (data);
//}

// void	execute(t_tree_node *root, t_manager *manager)
// {
// 	//if (root->left == NULL && root->right == NULL)
// 	//if (!root->right && root->refine_data.cmd_args && is_builtin(root->refine_data.cmd_args[0]))
// 	//	do_single_builtin(root->refine_data, &manager);
// 	//else
// 		exec_cmd_in_child(root, manager);
// }

//exec_in_while(t_tree_node *root)
//{
//	t_tree_node *ptr;

//	ptr = root;
//	while (ptr->left != NULL)
//		ptr = ptr->left;
//	do_exec(ptr); //forkし、ストリームを変え、実行、prev_fd＆last_pidを更新
//	while (ptr != NULL)
//	{
//		if (is_cmd_node())
//			de_exec(ptr->right->exec_arg_data); //forkし、ストリームを変え、実行、prev_fd＆last_pidを更新
//		ptr = ptr->prev;
//	}
//}
