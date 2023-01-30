#include "tree.h"

void	free_tree(t_tree *node, void (*del)(void *))
{
	if (node == 0)
		return ;
	if (node->parent && node->parent->left == node)
		node->parent->left = NULL;
	if (node->parent && node->parent->right == node)
		node->parent->right = NULL;
	free_tree(node->left, del);
	free_tree(node->right, del);
	free_tree_node(node, del);
}
