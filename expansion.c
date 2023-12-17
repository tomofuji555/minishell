#include "execute.h"

do_exec(t_tree_node *current)
{
	//ハンドラーに値を入れる

}

exec_in_dfs(t_tree_node *tree_root)
{
	// t_tree_node *current;
	t_exec_handler	handler;

	handler.current = tree_root;
	if (handler.current->left != NULL)
		run_exec_in_dfs(handler.current->left);
	if (handler.current->cmd_tokens != NULL)
		do_exec(handler.current);
	if(handler.current->right != NULL)
		run_exec_in_dfs(handler.current->right);
}




