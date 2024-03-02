/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:13:32 by toshi             #+#    #+#             */
/*   Updated: 2024/03/02 14:35:54 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// __attribute__((destructor))
// static void destructor() {
//    system("leaks -q minishell");
// }

// // tokenizeの確認用
// int main()
// {
// 	char *str1 = " 		 ls -a|l naln>la ><<<$AA\"\"A>||>BB$B$<<CCC<<>DDD <<<LLL";
// 	char *str2 = "gnal|n'ga'<<<nga||lng$\'alnglag\"anlgn\'gna ";
// 	char *str3 = " abc d eg";
// 	char *str4 = "ggg\"gh\" hhhh";
// 	char *str5 = "aaa$\"ABCD\" $\'ABCDEF\' \"abc\'defg\" ";
// 	char *str6 = "$$$\"ABC\" $$$\"\" \"ABC\" \"\" ";
//	char *str7 = ">  a\"$PWD\" ls <	 ppp|pwd >>   ll<<   d>> l >d";
// 	t_token *head = tokenize(str7);
//	remove_space_afrer_redir(&head);
// 	print_tkn_lst(head);
// 	free_tkn_lst(head);
// }

// // push_redirの確認
// int main()
// {
// 	t_manager manager;
	
// 	char *str = ">k< a cat |> g<b cat -e |<a cat";
// 	manager = init();
// 	t_token *tkn_head = tokenize(str);
// 	if (tkn_head == NULL)
// 		return (1);
// 	t_tree_node *tnode_head = parse(tkn_head);
// 	print_init_of_tnode_lst(tnode_head);
// }

 // parserの確認 syntax_errorなし
// int main(int argc, char **argv)
// {
// 	char *str1 = "cat >  aaa$PED$\"PWD\"  aaa| cat>\"$PWD\"$ECHO <<kkk | aaa<<gaga>>glnagal";
// 	t_token *tkn_head = tokenize(str1);
// 	print_tkn_lst(tkn_head);
// 	t_tree_node *tnode_head = parse(tkn_head);
// 	print_init_of_tnode_lst(tnode_head);
// 	free_tnode_lst(tnode_head);
// }

//// expansion_env_of_tknの確認
//int main()
//{
//	char *str1 = "  $AA aaaa";
//	char *str2 = "cat >  aaa$PWD$\"SSS\">>  aaa$PWD$\"PWD\"  aaa| cat>\"$PWD\"$ECHO <<kkk |$LS$";
//	char *str3 = "$LS'aaa'$'bbb'$LS'sss'";
//	char *str4 = "$ZZZ>\"$PWD\"$ECHO<<kkk$PPP cat >  aaa$PWD$\"PWD\"  aaa|$LS$";
//	char *str5 = "ls |$LS$";
//	t_token *tkn_head = tokenize(str4);
//	if (tkn_head == NULL)
//		return (1);
//	t_tree_node *tnode_head = parse(tkn_head);
//	printf("---------------------------------------------------------------------------------\n");
//	expansion(tnode_head);
//	print_exec_of_tnode_lst(tnode_head);
//	free_tnode_lst(tnode_head);
//}

// // expansion_env_in_dquote単体の確認
// int main()
// {
// 	char *str = ft_strdup("$PWD $ $NO $HOME$ZERO$HOME");
// 	printf("%s\n", str);
// 	printf("----------old----------\n");

// 	char *new_str = expand_env_in_dquote(str);
// 	printf("----------new----------\n");
// 	printf("sum %zd; %s;\n", ft_strlen(new_str) + 1,new_str);

// 	char *sumstr = "/Users/toshi/Desktop/42/42cursus/minishell $  /Users/toshi/Users/toshi";
// 	printf("sumstr %zd; %s;\n", ft_strlen(sumstr) + 1,sumstr);
// 	free(new_str);
// }

// // redir_listの確認
// int main(int argc, char **argv)
// {
// 	char *str1 = "cat >  aaa$PED$\"PWD\"  aaa| cat>\"$PWD\"$ECHO <<kkk | aaa<<gaga>>glnagal";
// 	t_token *tkn_head = tokenize(str1);
// 	if (tkn_head == NULL)
// 		return (1);
// 	t_tree_node *tnode_head = parse(tkn_head);
// 	tnode_print_lst(tnode_head);
// 	printf("---------------------------------------------------------------------------------\n");
// 	tnode_print_lst(tnode_head);
// 	tnode_free_lst(tnode_head);
// }

//heredoc用テスト
// int main()
// {
// 	char *line;
// 	char *filename = NULL;

// 	while(1)
// 	{
// 		line = readline("minishell $ ");
// 		if (line == NULL)
// 			printf("error\n");
// 		else
// 		{
// 			if(*line != '\0')
// 			{
// 				add_history(line);
// 				if (ft_strcmp(line, "heredoc") == 0)
// 					filename = run_heredoc("heredoc");
// 				if (ft_strcmp(line, "end") == 0)
// 				{
// 					free(line);
// 					break;
// 				}
// 			}
// 			free(line);
			
// 			// printf("line=\"%s\"", line);
// 			// printf("\n");
// 			// free(line);
// 		}
// 	}
// 	printf("file名 %s\n", filename);
// 	free(filename);
// }

int main()
{
	t_manager manager;
	
	char *str1 = "ls |cat -e | rev | cat -e | rev | cat |cat -e | rev | cat -e | cat | cat | cat | cat | rev | rev |head -n 5";
	char *str2 = "cat | cat |ls ";
	char *str3 = "<./a cat <./b|>./c cat ";
	char *str4 = "<a>c cat <b";
	char *str5 = "ls | rev | aaa";
	char *str6 = " << aaa cat | cat |  rev > x";
	char *str7 = " <  	x  cat | cat ";
	char *str8 = "aaa | cat | ls";
	char *str9 = "echo $HOME$1$@$USER$_KK";
	manager = init();
	t_token *tkn_head = tokenize(str9);
	if (tkn_head == NULL)
		return (1);
	t_tree_node *tnode_head = parse(tkn_head);
	expansion(tnode_head);
	try_heredoc(tnode_head);
	_exec(tnode_head, &manager);
	remove_tmpfile(tnode_head);
	free_tnode_lst(tnode_head);
	free_multi_strs(manager.envp);
	printf("終了ステータスは%d\n", manager.exit_status);
}


