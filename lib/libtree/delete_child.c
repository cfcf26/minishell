#include "tree.h"

t_tree	*delete_child(t_tree *tree, int rl)
{
	t_tree	*old;

	if (rl == LEFT)
	{
		old = tree->left;
		tree->left = NULL;
		return (old);
	}
	old = tree->right;
	tree->right = NULL;
	return (old);
}
