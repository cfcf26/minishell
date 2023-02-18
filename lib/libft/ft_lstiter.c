#include "libft.h"

void	ft_lstiter(t_list *lst, t_action_1 f)
{
	if (f == 0)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
