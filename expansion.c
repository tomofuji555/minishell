#include "minishell.h"


do_exec(t_tree_node *tree_node)
{
	//ハンドラーに値を入れる

}

exec_in_dfs(t_tree_node *tree_root)
{
	t_tree_node *current;

	current = tree_root;
	if (current->left != NULL)
		run_exec_in_dfs(current->left);
	if (current->cmd_tokens != NULL)
		do_exec(current);
	if(current->right != NULL)
		run_exec_in_dfs(current->right);
}




