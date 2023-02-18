#include <stdlib.h>
#include "libft.h"

void	ft_lstdelone(t_list *lst, t_action_1 del)
{
	if (lst == 0)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}
