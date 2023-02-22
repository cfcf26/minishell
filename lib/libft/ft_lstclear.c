#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, t_action_1 del)
{
	t_list	*next;

	if (lst == 0)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
}
