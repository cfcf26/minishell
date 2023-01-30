#include "tree.h"

t_tree	*add_new_tree_node(t_tree *origin, int dir1, void *c, int dir2)
{
	return (add_tree_node(origin, dir1, new_tree_node(c), dir2));
}
