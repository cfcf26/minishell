#ifndef TREE_H
# define TREE_H

# include <stdlib.h>
# include <stdio.h>

# define PARENT 0
# define LEFT 1
# define RIGHT 2
# define PREORDER 0
# define INORDER 1
# define POSTORDER 2

typedef struct s_tree
{
	void			*data;
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

t_tree	*new_tree_node(void *data);
void	free_tree_node(t_tree *node, void (*del)(void *));
void	free_tree(t_tree *node, void (*del)(void *));
t_tree	*delete_child(t_tree *tree, int rl);
t_tree	*add_tree_node(t_tree *origin, int dir1, t_tree *n, int dir2);
t_tree	*add_new_tree_node(t_tree *origin, int dir1, void *d, int dir2);
void	iterate_tree(t_tree *tree, void (*f)(void *), int order);
t_tree	*get_child(t_tree *tree, int rl);
t_tree	*get_root(t_tree *tree);

#endif
