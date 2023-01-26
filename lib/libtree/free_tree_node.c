#include "tree.h"

void	free_tree_node(t_tree *node, void (*del)(void *))
{
	if (del)
		del(node->data);
	free(node);
}
