#include <stdio.h>
#include "builtin.h"
#include "model.h"

int	builtin_env(t_list *argv)
{
	t_list	*lst;

	(void)argv;
	lst = data()->envp;
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
	return (0);
}
