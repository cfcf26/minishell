#include "tree.h"

t_tree	*get_root(t_tree *tree)
{
	if (tree == NULL)
		return (NULL);
	while (tree->parent)
		tree = tree->parent;
	return (tree);
}
