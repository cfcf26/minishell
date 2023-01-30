#include "tree.h"

t_tree	*new_tree_node(void *data)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	if (new_node == NULL)
	{
		perror("tree node malloc fail");
		exit(1);
	}
	new_node->data = data;
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
