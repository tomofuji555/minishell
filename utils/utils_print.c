/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <tofujiwa@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:36:35 by toshi             #+#    #+#             */
/*   Updated: 2024/04/20 17:39:16 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../libft/libft.h"

void	wc(char *str)
{
	if (str == NULL)
	{
		ft_putendl_fd("test", STDERR_FILENO);
		return ;
	}
	ft_putendl_fd(str, STDERR_FILENO);
}

//tokenizeの際、firstとlastの範囲がとれているか
void	print_to_last(char *first, char *last)
{
	printf("%d==", (int)(last - first + 1));
	while (first != last)
	{
		printf("%c", *first);
		first++;
	}
	printf("%c;\n", *first);
}

//tokenの内容をprint
void	print_token_list(t_token *ptr)
{
	while (ptr != NULL)
	{	
		if (ptr->kind == TKN_SPACE)
			printf("kind= SPACE; val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_TEXT)
			printf("kind= TEXT;  val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_S_QUOTE)
			printf("kind= S_Q;   val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_D_QUOTE)
			printf("kind= D_Q;   val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_ENV)
			printf("kind= ENV;   val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_PIPE)
			printf("kind= PIPE;  val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_IN_FILE)
			printf("kind= IN;    val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_HEREDOC)
			printf("kind= HERE;  val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_OUT_FILE)
			printf("kind= OUT;   val=%s;\n", ptr->val);
		else if (ptr->kind == TKN_APPEND_FILE)
			printf("kind= APP;   val=%s;\n", ptr->val);
		ptr = ptr->next;
	}
}

void	print_cmd_args(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		printf("%zd=%s;\n", i, strs[i]);
		i++;
	}
}

void	print_redir_list(t_redir *head)
{
	t_redir	*ptr;

	ptr = head;
	while (ptr != NULL)
	{	
		if (ptr->kind == REDIR_IN_FILE)
			printf("kind= IN;   val=%s;\n", ptr->val);
		else if (ptr->kind == REDIR_HEREDOC)
			printf("kind= HERE; val=%s;\n", ptr->val);
		else if (ptr->kind == REDIR_HEREDOC_NO_EXPAND)
			printf("kind= NOEX; val=%s;\n", ptr->val);
		else if (ptr->kind == REDIR_OUT_FILE)
			printf("kind= OUT;  val=%s;\n", ptr->val);
		else if (ptr->kind == REDIR_APPEND_FILE)
			printf("kind= APP;  val=%s;\n", ptr->val);
		ptr = ptr->next;
	}
}
