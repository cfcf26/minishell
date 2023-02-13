#include "minishell.h"

void	init_envp(char **envp)
{
	t_list	*node;

	while (envp[0])
	{
		node = ft_lstnew(*envp);
		if (node == NULL)
			exit(1); // null guard
		ft_lstadd_back(&(data()->envp), node);
		envp++;
	}
}
