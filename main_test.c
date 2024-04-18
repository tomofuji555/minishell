/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:13:32 by toshi             #+#    #+#             */
/*   Updated: 2024/04/19 00:18:42 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/utils.h"
#include "expansion/expansion.h"
#include "token_tozeki/tokenize.h"
#include "parse_tozeki/parse.h"

int	signal_flag = 0;

// __attribute__((destructor))
// static void destructor() {
// system("leaks -q minishell");
// }

////環境変数リストのテスト
//t_env *envp_ver2();
//int main()
//{
//	t_env *head;
//	head = envp_ver2();
//	print_env_list(head);
//}

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
//	char *str8 = "bgakbga$_aganlanan_gnalga_nangal$$anglannal";
// 	t_token *head = tokenize(str8);
//	del_space_afrer_redir(&head);
// 	print_tkn_list(head);
// 	free_tkn_list(head);
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
// 	print_init_of_tnode_list(tnode_head);
// }

 // parserの確認 syntax_errorなし
// int main(int argc, char **argv)
// {
// 	char *str1 = "cat >  aaa$PED$\"PWD\"  aaa| cat>\"$PWD\"$ECHO <<kkk | aaa<<gaga>>glnagal";
// 	t_token *tkn_head = tokenize(str1);
// 	print_tkn_list(tkn_head);
// 	t_tree_node *tnode_head = parse(tkn_head);
// 	print_init_of_tnode_list(tnode_head);
// 	free_tnode_list(tnode_head);
// }

// expansion_env_of_tknの確認
int main()
{
	t_manager manager;
	
	char *str1 = "  $AA aaaa";
	char *str2 = "cat >  aaa$PWD$\"SSS\">>  aaa$PWD$\"PWD\"  aaa| cat>\"$PWD\"$ECHO <<kkk |$LS$";
	char *str3 = "$LS'aaa'$'bbb'$LS'sss'";
	char *str4 = "$ZZZ>\"$PWD\"$ECHO<<kkk$PPP cat >  aaa$PWD$\"PWD\"  aaa|$LS$";
	char *str5 = "ls |$LS$";
	char *str6 = "cat >aaa$PWD<bbb$PWD ccc$PWD |$LS$";
	char *str7 = "$NO < $NO  >$NO | ls";
	manager = initialize();
	t_token *tkn_head = tokenize(str7);
	if (tkn_head == NULL)
		return (1);
	t_tree_node *tnode_head = parse(tkn_head);
	// printf("---------------------------------------------------------------------------------\n");
	expansion(tnode_head, &manager);
	print_exec_of_tnode_list(tnode_head);
	free_env_list(manager.env_list);
	free_tnode_list(tnode_head);
}

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
// 	tnode_print_list(tnode_head);
// 	printf("---------------------------------------------------------------------------------\n");
// 	tnode_print_list(tnode_head);
// 	tnode_free_list(tnode_head);
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
// 				if (is_equal_str(line, "heredoc"))
//					filename = run_heredoc("heredoc");
// 				if (is_equal_str(line, "heredoc"))
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

// //cdのテスト
// int main(int argc, char **argv)
// {
// 	char *full_path;
	
// 	if (argc != 2 + 1)
// 	{
// 		perror_arg2("cd","error");
// 		return (1);
// 	}
// 	// full_path = expand_path(argv[1], argv[2]);
// 	expand_path(argv[1], argv[2]);
// 	// if (chdir(argv[1]) == -1)
// 	// {
// 	// 	perror("cd");
// 	// 	return (1);
// 	// }
// 	// update_pwd(manager, argv[1]);
// 	return (0);
// }


// //strlcat_ret_catlenテスト
// int main()
// {
// 	size_t len = 5;
// 	char str[len];
// 	int i = 0;
// 	str[i++] = '0';
// 	str[i++] = '1';
// 	str[i++] = '2';
// 	str[i++] = '3';
// 	str[i++] = '4';
// 	char *s1 = "abcdef";
// 	size_t ret = strlcat_ret_catlen(str, s1, len);
// 	printf("str=%s;, ret=%zd;\n", str, ret);
// }

// //str_n_back用テスト
// int main(int argc , char **argv)
// {
// 	if (argc < 4)
// 		return (1);
// 	printf("%s;\n", strchr_n_back(argv[1], argv[2][0], ft_atoi(argv[3])));
// }

// int main()
// {
// 	t_manager manager;
	
// 	char *str1 = "ls |cat -e | rev | cat -e | rev | cat |cat -e | rev | cat -e | cat | cat | cat | cat | rev | rev |head -n 5";
// 	char *str2 = "cat | cat |ls ";
// 	char *str3 = "<./a cat <./b|>./c cat ";
// 	char *str4 = "<a>c cat <b";
// 	char *str5 = "ls | rev | aaa";
// 	char *str6 = " << aaa cat | cat |  rev > x";
// 	char *str7 = " <  	x  cat | cat ";
// 	char *str8 = "aaa | cat | ls";
// 	char *str9 = "echo $HOME$1$@$USER$_KK";
// 	char *str10 = "cat << aaa";
// 	char *str11 = "ls >$?\"kkk$? kkk$lll\"   ";
// 	char *str12 = "ls >$?\"kkk$? kkk\"   ";
// 	manager = initialize();
// 	t_token *tkn_head = tokenize(str12);
// 	if (tkn_head == NULL)
// 		return (1);
// 	t_tree_node *tnode_head = parse(tkn_head);
// 	expansion(tnode_head, &manager);
// 	print_exec_of_tnode_list(tnode_head);
// 	try_heredoc(tnode_head, &manager);
// 	if (signal_flag == 0)
// 		execute(tnode_head, &manager);
// 	rm_heredoc_tmp(tnode_head);
// 	free_tnode_list(tnode_head);
// 	printf("終了ステータスは%d\n", ft_atoi(manager.exit_status));
// 	finalize(&manager);
// }
