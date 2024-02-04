/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:13:32 by toshi             #+#    #+#             */
/*   Updated: 2024/02/02 21:08:18 by toshi            ###   ########.fr       */
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
// 	t_token *head = tokenize(str5);
// 	tkn_print_lst(head);
// 	tkn_free_lst(head);
// }

// // parserの確認 syntax_errorなし
// int main(int argc, char **argv)
// {
// 	char *str1 = "cat >  aaa$PED$\"PWD\"  aaa| cat>\"$PWD\"$ECHO <<kkk | aaa<<gaga>>glnagal";
// 	t_token *tkn_head = tokenize(str1);
// 	tkn_print_lst(tkn_head);
// 	t_tree_node *tnode_head = parse(tkn_head);
// 	tnode_print_lst(tnode_head);
// 	tnode_free_lst(tnode_head);
// }

// expand全体の確認
int main()
{
	char *str1 = "  $AA aaaa";
	char *str2 = "cat >  aaa$PWD$\"PWD\"  aaa| cat>\"$PWD\"$ECHO <<kkk |$LS$";
	char *str3 = "$LS$";
	t_token *tkn_head = tokenize(str2);
	if (tkn_head == NULL)
		return (1);
	t_tree_node *tnode_head = parse(tkn_head);
	// tnode_print_lst(tnode_head);
	printf("---------------------------------------------------------------------------------\n");
	expansion(tnode_head);
	tnode_print_lst(tnode_head);
	// tnode_free_lst(tnode_head);
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
// 	tnode_print_lst(tnode_head);
// 	printf("---------------------------------------------------------------------------------\n");
// 	tnode_print_lst(tnode_head);
// 	tnode_free_lst(tnode_head);
// }

// int main()
// {
// 	char *str = "cat< a.txt$PWD\"nalfa\" -e |  ls $PWD\"agnalnga\"  >    lll ";
// 	t_token *tkn_head = tokenize(str);
// 	if (tkn_head == NULL)
// 		return (1);
// 	t_tree_node *tnode_head = parse(tkn_head);
// 	// tnode_print_lst(tnode_head);
// 	printf("---------------------------------------------------------------------------------\n");
// 	expansion(tnode_head);
// 	tnode_print_lst(tnode_head);
// 	tnode_free_lst(tnode_head);
// }
