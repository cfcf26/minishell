#include "minishell.h"

t_list	*token_filter(t_list *lst, t_token_type type)
{
	t_list	*res;
	t_list	*node;

	res = NULL;
	while (lst)
	{
		if (((t_token *)(lst->content))->type == type)
		{
			node = ft_lstnew(lst->content);
			if (node == NULL)
				exit(1); // malloc error
			ft_lstadd_back(&res, node);
		}
		lst = lst->next;
	}
	return (res);
}
