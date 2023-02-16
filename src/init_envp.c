#include "minishell.h"

void	init_envp(char **envp)
{
	t_list	*node;

	while (envp[0])
	{
		node = ft_lstnew_guard(ft_strdup(*envp));
		ft_lstadd_back(&(data()->envp), node);
		envp++;
	}
}
