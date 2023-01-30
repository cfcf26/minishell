#include "tree.h"

t_tree	*get_child(t_tree *tree, int rl)
{
	if (tree == NULL)
		return (NULL);
	if (rl == LEFT)
		return tree->left;
	return tree->right;
}
