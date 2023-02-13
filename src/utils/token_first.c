#include "minishell.h"

t_token	*token_first(t_list *lst, t_token_type type)
{
	while (lst)
	{
		if (((t_token *)(lst->content))->type == type)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}
