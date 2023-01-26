#include "tree.h"

t_tree	*add_tree_node(t_tree *origin, int d1, t_tree *new_node, int d2)
{
	if (origin == NULL || new_node == NULL)
		return (new_node);
	if (d1 == PARENT)
	{
		new_node->parent = origin;
		if (d2 == LEFT)
			origin->left = new_node;
		if (d2 == RIGHT)
			origin->right = new_node;
	}
	if (d2 == PARENT)
	{
		origin->parent = new_node;
		if (d1 == LEFT)
			new_node->left = origin;
		if (d1 == RIGHT)
			new_node->right = origin;
	}
	return (new_node);
}
